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

        // Add hover sound effect (optional)
        this.addHoverEffects();
    }

    handleClick(event) {
        const emoji = event.target;
        const animation = this.getRandomAnimation();
        
        // Remove any existing animation
        this.animations.forEach(anim => {
            emoji.classList.remove(anim);
        });
        
        // Force reflow
        void emoji.offsetWidth;
        
        // Add new animation
        emoji.classList.add(animation);
        
        // Create ripple effect
        this.createRipple(emoji);
        
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
        
        ripple.style.width = ripple.style.height = size + 'px';
        ripple.style.left = (event.clientX - rect.left - size / 2) + 'px';
        ripple.style.top = (event.clientY - rect.top - size / 2) + 'px';
        
        element.appendChild(ripple);
        
        setTimeout(() => {
            ripple.remove();
        }, 600);
    }

    addHoverEffects() {
        // Add subtle hover effect
        this.emojis.forEach(emoji => {
            emoji.addEventListener('mouseenter', () => {
                emoji.style.transform = 'scale(1.1)';
            });
            
            emoji.addEventListener('mouseleave', () => {
                emoji.style.transform = 'scale(1)';
            });
        });
    }
}

// Initialize when DOM is ready
document.addEventListener('DOMContentLoaded', () => {
    new EmojiAnimator();
    
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
});

// Add CSS for ripple effect
const style = document.createElement('style');
style.textContent = `
    .ripple-effect {
        position: absolute;
        border-radius: 50%;
        background: rgba(0, 0, 0, 0.1);
        transform: scale(0);
        animation: ripple-animation 0.6s ease-out;
        pointer-events: none;
    }
    
    @keyframes ripple-animation {
        to {
            transform: scale(4);
            opacity: 0;
        }
    }
    
    .emoji {
        position: relative;
        overflow: visible;
    }
`;
document.head.appendChild(style);