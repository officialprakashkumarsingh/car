// Game canvas and context
const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');

// Constants
const gridSize = 20;
const tileCount = canvas.width / gridSize;

// Snake properties
let snake = [
    { x: 10, y: 10 }
];
let velocityX = 0;
let velocityY = 0;
let foodX;
let foodY;
let gameOver = false;
let score = 0;

// Game loop
function gameLoop() {
    if (gameOver) {
        drawGameOver();
        return;
    }
    
    // Clear canvas
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    
    // Update snake position
    moveSnake();
    
    // Check for collisions
    checkCollision();
    
    // Draw everything
    drawSnake();
    drawFood();
    updateScore();
    
    // Continue game loop with a delay to control game speed
    setTimeout(gameLoop, 100);
}

// Move the snake based on current velocity
function moveSnake() {
    // Calculate new head position
    const head = { x: snake[0].x + velocityX, y: snake[0].y + velocityY };
    
    // Add new head to the beginning of snake array
    snake.unshift(head);
    
    // Check if snake ate food
    if (head.x === foodX && head.y === foodY) {
        score++;
        generateFood();
    } else {
        // Remove tail if no food is eaten
        snake.pop();
    }
}

// Check for collisions with walls or self
function checkCollision() {
    const head = snake[0];
    
    // Wall collision
    if (head.x < 0 || head.x >= tileCount || head.y < 0 || head.y >= tileCount) {
        gameOver = true;
    }
    
    // Self collision
    for (let i = 1; i < snake.length; i++) {
        if (head.x === snake[i].x && head.y === snake[i].y) {
            gameOver = true;
        }
    }
}

// Generate new food position randomly
function generateFood() {
    foodX = Math.floor(Math.random() * tileCount);
    foodY = Math.floor(Math.random() * tileCount);
    
    // Ensure food doesn't spawn on snake
    for (let segment of snake) {
        if (foodX === segment.x && foodY === segment.y) {
            generateFood(); // Recursive call if food spawns on snake
        }
    }
}

// Draw the snake on the canvas
function drawSnake() {
    for (let segment of snake) {
        ctx.fillStyle = 'green';
        ctx.fillRect(segment.x * gridSize, segment.y * gridSize, gridSize - 2, gridSize - 2);
    }
}

// Draw the food on the canvas
function drawFood() {
    ctx.fillStyle = 'red';
    ctx.fillRect(foodX * gridSize, foodY * gridSize, gridSize - 2, gridSize - 2);
}

// Update the score display in the DOM
function updateScore() {
    document.getElementById('score').textContent = score;
}

// Draw game over message when game ends
function drawGameOver() {
    ctx.fillStyle = 'black';
    ctx.font = '30px Arial';
    ctx.textAlign = 'center';
    ctx.fillText('Game Over!', canvas.width / 2, canvas.height / 2 - 15);
    ctx.font = '20px Arial';
    ctx.fillText('Score: ' + score, canvas.width / 2, canvas.height / 2 + 20);
}

// Reset game state to start a new game
function resetGame() {
    snake = [{ x: 10, y: 10 }];
    velocityX = 0;
    velocityY = 0;
    score = 0;
    gameOver = false;
    generateFood();
    gameLoop();
}

// Handle keyboard input for snake direction
document.addEventListener('keydown', (e) => {
    if (gameOver) return;
    
    // Prevent reversing direction directly into the snake's body
    switch (e.key) {
        case 'ArrowUp':
            if (velocityY !== 1) {
                velocityX = 0;
                velocityY = -1;
            }
            break;
        case 'ArrowDown':
            if (velocityY !== -1) {
                velocityX = 0;
                velocityY = 1;
            }
            break;
        case 'ArrowLeft':
            if (velocityX !== 1) {
                velocityX = -1;
                velocityY = 0;
            }
            break;
        case 'ArrowRight':
            if (velocityX !== -1) {
                velocityX = 1;
                velocityY = 0;
            }
            break;
    }
});

// Attach restart functionality to the button
document.getElementById('restartButton').addEventListener('click', resetGame);

// Generate initial food position
generateFood();

// Start the game loop
gameLoop();