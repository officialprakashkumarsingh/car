#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>

// Canvas structure to hold pixel data and dimensions
typedef struct {
    int width;
    int height;
    uint32_t* pixels; // 32-bit color (RGBA)
} Canvas;

// Function declarations

/**
 * Initialize a canvas with the given width and height.
 * Allocates memory for pixel data.
 * @param canvas Pointer to the Canvas structure to initialize.
 * @param width Width of the canvas in pixels.
 * @param height Height of the canvas in pixels.
 * @return 0 on success, -1 on memory allocation failure.
 */
int canvas_init(Canvas* canvas, int width, int height);

/**
 * Free the memory allocated for the canvas pixel data.
 * @param canvas Pointer to the Canvas structure to destroy.
 */
void canvas_destroy(Canvas* canvas);

/**
 * Clear the canvas by setting all pixels to the specified color.
 * @param canvas Pointer to the Canvas structure.
 * @param color 32-bit color value (RGBA) to fill the canvas with.
 */
void canvas_clear(Canvas* canvas, uint32_t color);

/**
 * Set the color of a specific pixel on the canvas.
 * Checks for bounds to prevent buffer overflow.
 * @param canvas Pointer to the Canvas structure.
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @param color 32-bit color value (RGBA) to set.
 * @return 0 on success, -1 if coordinates are out of bounds.
 */
int canvas_set_pixel(Canvas* canvas, int x, int y, uint32_t color);

/**
 * Get the color of a specific pixel on the canvas.
 * @param canvas Pointer to the Canvas structure.
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @return The 32-bit color value (RGBA) of the pixel, or 0 if out of bounds.
 */
uint32_t canvas_get_pixel(Canvas* canvas, int x, int y);

#endif // CANVAS_H