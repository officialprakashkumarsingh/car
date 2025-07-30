#ifndef THIS_H
#define THIS_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include <chrono>
#include <thread>

namespace NeutralDesign {
    
    // Neutral color palette constants
    namespace Colors {
        constexpr char* BG_PRIMARY = "#faf9f7";
        constexpr char* BG_SECONDARY = "#f5f4f2";
        constexpr char* BG_TERTIARY = "#edebe8";
        constexpr char* TEXT_PRIMARY = "#2c2c2c";
        constexpr char* TEXT_SECONDARY = "#6b6b6b";
        constexpr char* TEXT_MUTED = "#a8a8a8";
        constexpr char* BORDER_LIGHT = "#e5e3e0";
        constexpr char* BORDER_MEDIUM = "#d1cfcb";
        constexpr char* ACCENT_SUBTLE = "#c7c4be";
    }
    
    // Emoji definitions
    struct Emoji {
        std::string icon;
        std::string name;
        std::string description;
        
        Emoji(const std::string& i, const std::string& n, const std::string& d)
            : icon(i), name(n), description(d) {}
    };
    
    // Animation types
    enum class AnimationType {
        BOUNCE,
        PULSE,
        SPIN,
        WIGGLE,
        NONE
    };
    
    // Animation configuration
    struct AnimationConfig {
        AnimationType type;
        int duration_ms;
        float intensity;
        
        AnimationConfig(AnimationType t = AnimationType::NONE, int d = 500, float i = 1.0f)
            : type(t), duration_ms(d), intensity(i) {}
    };
    
    // Emoji manager class
    class EmojiManager {
    private:
        std::vector<Emoji> emojis;
        std::map<std::string, AnimationConfig> animations;
        
    public:
        EmojiManager() {
            initializeEmojis();
            initializeAnimations();
        }
        
        void initializeEmojis() {
            emojis.emplace_back("🌿", "leaf", "Natural element");
            emojis.emplace_back("😊", "smile", "Happy face");
            emojis.emplace_back("🌸", "blossom", "Peaceful flower");
            emojis.emplace_back("🕊️", "dove", "Calm bird");
            emojis.emplace_back("☕", "coffee", "Relaxing drink");
            emojis.emplace_back("🌙", "moon", "Dream state");
            emojis.emplace_back("✨", "sparkle", "Gentle shine");
            emojis.emplace_back("🏡", "home", "Comfort space");
            emojis.emplace_back("🎯", "target", "Focus point");
            emojis.emplace_back("⚡", "lightning", "Feature highlight");
            emojis.emplace_back("🎨", "palette", "Design element");
            emojis.emplace_back("📐", "ruler", "Precision tool");
            emojis.emplace_back("🎭", "mask", "Interactive element");
            emojis.emplace_back("🎬", "clapper", "Animation control");
            emojis.emplace_back("💚", "green heart", "Love and care");
        }
        
        void initializeAnimations() {
            animations["bounce"] = AnimationConfig(AnimationType::BOUNCE, 500, 1.0f);
            animations["pulse"] = AnimationConfig(AnimationType::PULSE, 600, 1.2f);
            animations["spin"] = AnimationConfig(AnimationType::SPIN, 600, 1.0f);
            animations["wiggle"] = AnimationConfig(AnimationType::WIGGLE, 500, 1.0f);
        }
        
        const std::vector<Emoji>& getEmojis() const { return emojis; }
        
        const AnimationConfig& getAnimation(const std::string& name) const {
            static AnimationConfig defaultConfig;
            auto it = animations.find(name);
            return it != animations.end() ? it->second : defaultConfig;
        }
        
        std::vector<std::string> getAnimationNames() const {
            std::vector<std::string> names;
            for (const auto& pair : animations) {
                names.push_back(pair.first);
            }
            return names;
        }
    };
    
    // CSS generator for neutral design
    class CSSGenerator {
    public:
        static std::string generateBaseCSS() {
            return R"(
:root {
    --bg-primary: #faf9f7;
    --bg-secondary: #f5f4f2;
    --bg-tertiary: #edebe8;
    --text-primary: #2c2c2c;
    --text-secondary: #6b6b6b;
    --text-muted: #a8a8a8;
    --border-light: #e5e3e0;
    --border-medium: #d1cfcb;
    --accent-subtle: #c7c4be;
}

* {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
}

body {
    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
    background-color: var(--bg-primary);
    color: var(--text-primary);
    line-height: 1.6;
}

.container {
    max-width: 800px;
    margin: 0 auto;
    padding: 2rem;
    min-height: 100vh;
}

.emoji {
    display: inline-block;
    font-size: 1.5em;
    cursor: pointer;
    transition: transform 0.3s ease;
    user-select: none;
}

.emoji:hover {
    transform: scale(1.1);
}

.emoji:active {
    transform: scale(0.9);
}

@keyframes bounce {
    0%, 100% { transform: translateY(0); }
    50% { transform: translateY(-10px); }
}

@keyframes pulse {
    0%, 100% { transform: scale(1); }
    50% { transform: scale(1.2); }
}

@keyframes spin {
    from { transform: rotate(0deg); }
    to { transform: rotate(360deg); }
}

@keyframes wiggle {
    0%, 100% { transform: rotate(0deg); }
    25% { transform: rotate(-10deg); }
    75% { transform: rotate(10deg); }
}

.bounce { animation: bounce 0.5s ease; }
.pulse { animation: pulse 0.6s ease; }
.spin { animation: spin 0.6s ease; }
.wiggle { animation: wiggle 0.5s ease; }
)";
        }
        
        static std::string generateResponsiveCSS() {
            return R"(
@media (max-width: 600px) {
    .container {
        padding: 1rem;
    }
    
    .emoji-grid {
        grid-template-columns: repeat(auto-fit, minmax(100px, 1fr));
        gap: 1rem;
    }
}
)";
        }
    };
    
    // JavaScript generator for emoji animations
    class JSGenerator {
    public:
        static std::string generateAnimationJS() {
            return R"(
class EmojiAnimator {
    constructor() {
        this.emojis = document.querySelectorAll('.emoji');
        this.animations = ['bounce', 'pulse', 'spin', 'wiggle'];
        this.init();
    }

    init() {
        this.emojis.forEach(emoji => {
            emoji.addEventListener('click', this.handleClick.bind(this));
            emoji.setAttribute('tabindex', '0');
            emoji.addEventListener('keydown', this.handleKeydown.bind(this));
        });
    }

    handleClick(event) {
        const emoji = event.target;
        const animation = this.animations[Math.floor(Math.random() * this.animations.length)];
        
        emoji.classList.remove(...this.animations);
        void emoji.offsetWidth;
        emoji.classList.add(animation);
        
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
}

document.addEventListener('DOMContentLoaded', () => {
    new EmojiAnimator();
});
)";
        }
    };
    
    // HTML generator for minimal structure
    class HTMLGenerator {
    public:
        static std::string generateMinimalHTML(const EmojiManager& manager) {
            std::string html = R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Neutral Minimal</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <main class="container">
        <header>
            <h1>Welcome to <span class="emoji">🌿</span> Neutral Space</h1>
            <p>A calm, minimal experience</p>
        </header>
        
        <section class="emoji-grid">)";
            
            for (const auto& emoji : manager.getEmojis()) {
                html += "\n            <div class=\"emoji-card\">\n";
                html += "                <span class=\"emoji\" data-name=\"" + emoji.name + "\">" + emoji.icon + "</span>\n";
                html += "                <p>" + emoji.description + "</p>\n";
                html += "            </div>";
            }
            
            html += R"(
        </section>
    </main>
    <script src="script.js"></script>
</body>
</html>)";
            
            return html;
        }
    };
    
    // Utility functions
    namespace Utils {
        inline void sleep(int milliseconds) {
            std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
        }
        
        inline std::string getCurrentTimestamp() {
            auto now = std::chrono::system_clock::now();
            auto time_t = std::chrono::system_clock::to_time_t(now);
            char buffer[100];
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time_t));
            return std::string(buffer);
        }
        
        inline bool isValidEmoji(const std::string& emoji) {
            return !emoji.empty() && emoji.size() >= 2 && emoji[0] & 0x80;
        }
    }
}

// Global instances
static NeutralDesign::EmojiManager globalEmojiManager;

// Export functions for external use
extern "C" {
    const char* get_emoji_by_index(int index) {
        const auto& emojis = globalEmojiManager.getEmojis();
        if (index >= 0 && index < static_cast<int>(emojis.size())) {
            return emojis[index].icon.c_str();
        }
        return "❓";
    }
    
    const char* get_animation_name(int index) {
        auto names = globalEmojiManager.getAnimationNames();
        if (index >= 0 && index < static_cast<int>(names.size())) {
            return names[index].c_str();
        }
        return "none";
    }
    
    void trigger_emoji_click(const char* emoji_text) {
        std::cout << "Emoji clicked: " << emoji_text << std::endl;
    }
}

#endif // THIS_H