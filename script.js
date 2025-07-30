// Game variables
const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');
const scoreElement = document.querySelector('.score');
const highScoreElement = document.querySelector('.high-score');
const startPauseButton = document.getElementById('startPause');
const difficultySelect = document.getElementById('difficulty');
const gameOverScreen = document.getElementById('gameOver');
const finalScoreElement = document.querySelector('.final-score');
const restartButton = document.getElementById('restart');
const eatSound = document.getElementById('eatSound');
const gameOverSound = document.getElementById('gameOverSound');

let gridSize = 20;
let tileCount = canvas.width / gridSize;
let snake = [{ x: 10, y: 10 }];
let food = { x: 15, y: 15 };
let dx = 0;
let dy = 0;
let score = 0;
let highScore = localStorage.getItem('highScore') || 0;
let gameLoop;
let isGameRunning = false;
let speed = 100; // Default medium speed

highScoreElement.textContent = `High Score: ${highScore}`;

// Adjust game speed based on difficulty selection
difficultySelect.addEventListener('change', () => {
    const level = difficultySelect.value;
    speed = level === 'easy' ? 150 : level === 'hard' ? 50 : 100;
    if (isGameRunning) {
        clearInterval(gameLoop);
        gameLoop = setInterval(gameLoopFunction, speed);
    }
});

// Start or pause the game
startPauseButton.addEventListener('click', () => {
    if (isGameRunning) {
        clearInterval(gameLoop);
        startPauseButton.textContent = 'Start';
        isGameRunning = false;
    } else {
        gameLoop = setInterval(gameLoopFunction, speed);
        startPauseButton.textContent = 'Pause';
        isGameRunning = true;
    }
});

// Restart the game after game over
restartButton.addEventListener('click', () => {
    resetGame();
    gameOverScreen.style.display = 'none';
    gameLoop = setInterval(gameLoopFunction, speed);
    startPauseButton.textContent = 'Pause';
    isGameRunning = true;
});

// Keyboard controls for directional input
document.addEventListener('keydown', changeDirection);

// Touch controls for mobile devices
let touchStartX = 0;
let touchStartY = 0;
canvas.addEventListener('touchstart', (e) => {
    touchStartX = e.touches[0].clientX;
    touchStartY = e.touches[0].clientY;
});
canvas.addEventListener('touchmove', (e) => {
    if (!isGameRunning) return;
    const touchX = e.touches[0].clientX;
    const touchY = e.touches[0].clientY;
    const diffX = touchX - touchStartX;
    const diffY = touchY - touchStartY;
    if (Math.abs(diffX) > Math.abs(diffY)) {
        if (diffX > 30 && dx !== -1) { dx = 1; dy = 0; }
        else if (diffX < -30 && dx !== 1) { dx = -1; dy = 0; }
    } else {
        if (diffY > 30 && dy !== -1) { dx = 0; dy = 1; }
        else if (diffY < -30 && dy !== 1) { dx = 0; dy = -1; }
    }
    touchStartX = touchX;
    touchStartY = touchY;
});

/**
 * Changes the direction of the snake based on key input.
 * Prevents reversing direction directly into itself.
 * @param {KeyboardEvent} event - The keydown event object.
 */
function changeDirection(event) {
    const keyPressed = event.key;
    if (keyPressed === 'ArrowUp' && dy !== 1) { dx = 0; dy = -1; }
    else if (keyPressed === 'ArrowDown' && dy !== -1) { dx = 0; dy = 1; }
    else if (keyPressed === 'ArrowLeft' && dx !== 1) { dx = -1; dy = 0; }
    else if (keyPressed === 'ArrowRight' && dx !== -1) { dx = 1; dy = 0; }
}

/**
 * Main game loop function that updates snake position, checks collisions,
 * and redraws the game state on the canvas.
 */
function gameLoopFunction() {
    // Move snake by adding a new head in the current direction
    const head = { x: snake[0].x + dx, y: snake[0].y + dy };
    snake.unshift(head);

    // Check if snake eats food
    if (head.x === food.x && head.y === food.y) {
        score += 10;
        scoreElement.textContent = `Score: ${score}`;
        eatSound.play().catch(error => console.log('Audio play error:', error));
        generateFood();
    } else {
        snake.pop(); // Remove tail if no food is eaten
    }

    // Check for wall collision
    if (head.x < 0 || head.x >= tileCount || head.y < 0 || head.y >= tileCount) {
        gameOver();
        return;
    }

    // Check for self collision
    for (let i = 1; i < snake.length; i++) {
        if (head.x === snake[i].x && head.y === snake[i].y) {
            gameOver();
            return;
        }
    }

    // Clear canvas and redraw
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // Draw snake with detailed styling
    ctx.fillStyle = 'green';
    for (let part of snake) {
        ctx.fillRect(part.x * gridSize, part.y * gridSize, gridSize - 2, gridSize - 2);
        ctx.strokeStyle = 'darkgreen';
        ctx.strokeRect(part.x * gridSize, part.y * gridSize, gridSize - 2, gridSize - 2);
    }
    // Draw food as a circle
    ctx.fillStyle = 'red';
    ctx.beginPath();
    ctx.arc(food.x * gridSize + gridSize / 2, food.y * gridSize + gridSize / 2, gridSize / 2 - 2, 0, Math.PI * 2);
    ctx.fill();
}

/**
 * Generates new food position randomly on the grid,
 * ensuring it doesn't overlap with the snake.
 */
function generateFood() {
    food.x = Math.floor(Math.random() * tileCount);
    food.y = Math.floor(Math.random() * tileCount);
    for (let part of snake) {
        if (food.x === part.x && food.y === part.y) {
            generateFood(); // Recursive call if food spawns on snake
        }
    }
}

/**
 * Handles game over state, stops the game loop, plays sound,
 * updates high score if necessary, and shows game over screen.
 */
function gameOver() {
    clearInterval(gameLoop);
    isGameRunning = false;
    startPauseButton.textContent = 'Start';
    gameOverSound.play().catch(error => console.log('Audio play error:', error));
    finalScoreElement.textContent = score;
    gameOverScreen.style.display = 'flex';
    if (score > highScore) {
        highScore = score;
        localStorage.setItem('highScore', highScore);
        highScoreElement.textContent = `High Score: ${highScore}`;
    }
}

/**
 * Resets game state to initial values for a new game.
 */
function resetGame() {
    snake = [{ x: 10, y: 10 }];
    food = { x: 15, y: 15 };
    dx = 0;
    dy = 0;
    score = 0;
    scoreElement.textContent = `Score: ${score}`;
}

// Initial draw to show the game state before starting
gameLoopFunction();