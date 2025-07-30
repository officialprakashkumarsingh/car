#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>
#include <stdbool.h>

// Forward declarations
typedef struct Canvas Canvas;
typedef struct Color Color;
typedef struct Point Point;
typedef struct Rect Rect;

// Color structure for RGBA values
struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

// Point structure for 2D coordinates
struct Point {
    int x;
    int y;
};

// Rectangle structure
struct Rect {
    int x;
    int y;
    int width;
    int height;
};

// Canvas structure for drawing operations
struct Canvas {
    int width;
    int height;
    Color* pixels;
    Color clear_color;
    Color stroke_color;
    Color fill_color;
    int stroke_width;
};

// Predefined neutral colors
static const Color NEUTRAL_WHITE = {250, 249, 247, 255};
static const Color NEUTRAL_LIGHT = {245, 244, 242, 255};
static const Color NEUTRAL_MID = {237, 235, 232, 255};
static const Color NEUTRAL_DARK = {107, 107, 107, 255};
static const Color NEUTRAL_TEXT = {44, 44, 44, 255};
static const Color TRANSPARENT = {0, 0, 0, 0};

// Function declarations
Canvas* canvas_create(int width, int height);
void canvas_destroy(Canvas* canvas);
void canvas_clear(Canvas* canvas);
void canvas_set_clear_color(Canvas* canvas, Color color);
void canvas_set_stroke_color(Canvas* canvas, Color color);
void canvas_set_fill_color(Canvas* canvas, Color color);
void canvas_set_stroke_width(Canvas* canvas, int width);

// Drawing primitives
void canvas_draw_pixel(Canvas* canvas, int x, int y);
void canvas_draw_line(Canvas* canvas, int x0, int y0, int x1, int y1);
void canvas_draw_rect(Canvas* canvas, int x, int y, int width, int height);
void canvas_fill_rect(Canvas* canvas, int x, int y, int width, int height);
void canvas_draw_circle(Canvas* canvas, int cx, int cy, int radius);
void canvas_fill_circle(Canvas* canvas, int cx, int cy, int radius);

// Utility functions
bool canvas_save_to_ppm(const Canvas* canvas, const char* filename);
void canvas_set_pixel(Canvas* canvas, int x, int y, Color color);
Color canvas_get_pixel(const Canvas* canvas, int x, int y);
bool canvas_is_valid_coordinate(const Canvas* canvas, int x, int y);

// Emoji drawing functions
void canvas_draw_emoji_smile(Canvas* canvas, int x, int y, int size);
void canvas_draw_emoji_leaf(Canvas* canvas, int x, int y, int size);
void canvas_draw_emoji_coffee(Canvas* canvas, int x, int y, int size);
void canvas_draw_emoji_moon(Canvas* canvas, int x, int y, int size);
void canvas_draw_emoji_sparkle(Canvas* canvas, int x, int y, int size);

// Animation support
typedef struct AnimationState {
    float progress;
    float duration;
    bool active;
} AnimationState;

void canvas_animate_emoji_bounce(Canvas* canvas, int x, int y, int size, AnimationState* anim);
void canvas_animate_emoji_pulse(Canvas* canvas, int x, int y, int size, AnimationState* anim);
void canvas_animate_emoji_spin(Canvas* canvas, int x, int y, int size, AnimationState* anim);

#endif // CANVAS_H