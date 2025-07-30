// Emoji animation controller
class EmojiAnimator {
    constructor() {
        this.emojis = document.querySelectorAll('.emoji');
        this.animations = ['bounce', 'pulse', 'spin', 'wiggle'];
        this.init();
    }

    init() {
        // Add click listeners to all emojis
        this.emojis.forEach(emoji => {
            emoji.addEventListener('click', this.handleClick.bind(this));
            emoji.setAttribute('tabindex', '0');
            emoji.addEventListener('keydown', this.handleKeydown.bind(this));
        });

        // Add hover effects
        this.addHoverEffects();
        
        // Add intersection observer for scroll animations
        this.addScrollAnimations();
    }

    handleClick(event) {
        const emoji = event.target;
        const animation = this.getRandomAnimation();
        
        // Remove any existing animation
        this.animations.forEach(anim => {
            emoji.classList.remove(anim);
        });
        
        // Force reflow to restart animation
        void emoji.offsetWidth;
        
        // Add new animation
        emoji.classList.add(animation);
        
        // Create ripple effect
        this.createRipple(emoji);
        
        // Add particle burst
        this.createParticleBurst(emoji);
        
        // Remove animation after completion
        setTimeout(() => {
            emoji.classList.remove(animation);
        }, 600);
    }

    handleKeydown(event) {
        if (event.key === 'Enter' || event.key === ' ') {
            event.preventDefault();
            this.handleClick(event);
        }
    }

    getRandomAnimation() {
        return this.animations[Math.floor(Math.random() * this.animations.length)];
    }

    createRipple(element) {
        const ripple = document.createElement('span');
        ripple.className = 'ripple-effect';
        
        const rect = element.getBoundingClientRect();
        const size = Math.max(rect.width, rect.height);
        
        ripple.style.cssText = `
            position: absolute;
            width: ${size}px;
            height: ${size}px;
            border-radius: 50%;
            background: rgba(150, 150, 150, 0.3);
            transform: scale(0);
            animation: ripple 0.6s ease-out;
            pointer-events: none;
            left: ${rect.width / 2 - size / 2}px;
            top: ${rect.height / 2 - size / 2}px;
        `;
        
        element.style.position = 'relative';
        element.appendChild(ripple);
        
        setTimeout(() => {
            ripple.remove();
        }, 600);
    }

    createParticleBurst(element) {
        const particles = 6;
        const colors = ['#c7c4be', '#d1cfcb', '#e5e3e0'];
        
        for (let i = 0; i < particles; i++) {
            const particle = document.createElement('span');
            particle.className = 'particle';
            
            const angle = (i / particles) * 360;
            const distance = 30 + Math.random() * 20;
            const color = colors[Math.floor(Math.random() * colors.length)];
            
            particle.style.cssText = `
                position: absolute;
                width: 4px;
                height: 4px;
                background: ${color};
                border-radius: 50%;
                pointer-events: none;
                left: 50%;
                top: 50%;
                transform: translate(-50%, -50%);
                animation: particle-burst 0.8s ease-out forwards;
                --angle: ${angle}deg;
                --distance: ${distance}px;
            `;
            
            element.appendChild(particle);
            
            setTimeout(() => {
                particle.remove();
            }, 800);
        }
    }

    addHoverEffects() {
        this.emojis.forEach(emoji => {
            emoji.addEventListener('mouseenter', () => {
                emoji.style.transform = 'scale(1.1)';
            });
            
            emoji.addEventListener('mouseleave', () => {
                emoji.style.transform = 'scale(1)';
            });
        });
    }

    addScrollAnimations() {
        const observer = new IntersectionObserver((entries) => {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                    entry.target.style.opacity = '1';
                    entry.target.style.transform = 'translateY(0)';
                }
            });
        }, { threshold: 0.1 });

        document.querySelectorAll('.emoji-card').forEach(card => {
            card.style.opacity = '0';
            card.style.transform = 'translateY(20px)';
            card.style.transition = 'opacity 0.6s ease, transform 0.6s ease';
            observer.observe(card);
        });
    }
}

// Add CSS for ripple and particle effects
const style = document.createElement('style');
style.textContent = `
    @keyframes ripple {
        to {
            transform: scale(2);
            opacity: 0;
        }
    }
    
    @keyframes particle-burst {
        0% {
            transform: translate(-50%, -50%) rotate(var(--angle)) translateX(0);
            opacity: 1;
        }
        100% {
            transform: translate(-50%, -50%) rotate(var(--angle)) translateX(var(--distance));
            opacity: 0;
        }
    }
`;

document.head.appendChild(style);

// Initialize emoji animator when DOM is ready
document.addEventListener('DOMContentLoaded', () => {
    new EmojiAnimator();
});

// Add smooth scroll behavior for internal links
document.querySelectorAll('a[href^="#"]').forEach(anchor => {
    anchor.addEventListener('click', function (e) {
        e.preventDefault();
        const target = document.querySelector(this.getAttribute('href'));
        if (target) {
            target.scrollIntoView({ behavior: 'smooth' });
        }
    });
});

// Add keyboard navigation for emoji cards
document.querySelectorAll('.emoji-card').forEach(card => {
    card.setAttribute('tabindex', '0');
    card.addEventListener('keydown', (e) => {
        if (e.key === 'Enter' || e.key === ' ') {
            e.preventDefault();
            const emoji = card.querySelector('.emoji');
            if (emoji) {
                emoji.click();
            }
        }
    });
});

// Add random emoji generator
class EmojiGenerator {
    constructor() {
        this.emojis = ['😊', '🌸', '🕊️', '☕', '🌙', '✨', '🌿', '🎯', '🏡', '⚡', '🎨', '📐', '🎭', '🎬', '💚', '🎵', '🌈', '⭐', '🦋', '🌺'];
    }

    getRandomEmoji() {
        return this.emojis[Math.floor(Math.random() * this.emojis.length)];
    }

    addRandomEmoji() {
        const emoji = document.createElement('span');
        emoji.className = 'emoji';
        emoji.textContent = this.getRandomEmoji();
        emoji.style.position = 'fixed';
        emoji.style.left = Math.random() * window.innerWidth + 'px';
        emoji.style.top = '-50px';
        emoji.style.fontSize = '2em';
        emoji.style.pointerEvents = 'none';
        emoji.style.zIndex = '1000';
        
        document.body.appendChild(emoji);
        
        // Animate falling
        let pos = -50;
        const fall = setInterval(() => {
            pos += 2;
            emoji.style.top = pos + 'px';
            
            if (pos > window.innerHeight) {
                clearInterval(fall);
                emoji.remove();
            }
        }, 20);
    }
}

// Easter egg: double-click anywhere to see falling emojis
let clickCount = 0;
let clickTimer;

document.addEventListener('click', () => {
    clickCount++;
    
    if (clickCount === 1) {
        clickTimer = setTimeout(() => {
            clickCount = 0;
        }, 300);
    } else if (clickCount === 2) {
        clearTimeout(clickTimer);
        clickCount = 0;
        
        const generator = new EmojiGenerator();
        for (let i = 0; i < 5; i++) {
            setTimeout(() => generator.addRandomEmoji(), i * 200);
        }
    }
});