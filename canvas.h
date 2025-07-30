#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <stdexcept>

/**
 * @class Canvas
 * @brief A simple console-based canvas for rendering 2D grid-based graphics.
 *        Useful for text-based games like Snake.
 */
class Canvas {
public:
    /**
     * @brief Constructor to initialize the canvas with specified dimensions.
     * @param width Width of the canvas in characters.
     * @param height Height of the canvas in characters.
     */
    Canvas(int width, int height);

    /**
     * @brief Destructor to clean up resources.
     */
    ~Canvas();

    /**
     * @brief Clear the canvas to a default state (all spaces).
     */
    void clear();

    /**
     * @brief Draw a character at the specified position on the canvas.
     * @param x X-coordinate (column).
     * @param y Y-coordinate (row).
     * @param ch Character to draw.
     * @throws std::out_of_range if coordinates are outside canvas bounds.
     */
    void draw(int x, int y, char ch);

    /**
     * @brief Draw a string starting at the specified position.
     * @param x X-coordinate (column).
     * @param y Y-coordinate (row).
     * @param str String to draw.
     * @throws std::out_of_range if starting coordinates are outside canvas bounds.
     */
    void drawString(int x, int y, const std::string& str);

    /**
     * @brief Render the current state of the canvas to the console.
     */
    void render();

    /**
     * @brief Get the width of the canvas.
     * @return Width in characters.
     */
    int getWidth() const;

    /**
     * @brief Get the height of the canvas.
     * @return Height in characters.
     */
    int getHeight() const;

private:
    int width_;                         // Canvas width
    int height_;                        // Canvas height
    std::vector<std::vector<char>> buffer_; // 2D buffer for storing canvas content
    std::mutex renderMutex_;            // Mutex for thread-safe rendering

    /**
     * @brief Check if the given coordinates are within canvas bounds.
     * @param x X-coordinate.
     * @param y Y-coordinate.
     * @return True if within bounds, false otherwise.
     */
    bool isWithinBounds(int x, int y) const;
};

#endif // CANVAS_H