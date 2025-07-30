#ifndef CANVAS_H
#define CANVAS_H

#include <SDL2/SDL.h>
#include <vector>
#include <utility>

class Canvas {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    int gridSize;
    int tileCount;

public:
    Canvas(int w, int h, int grid);
    ~Canvas();
    
    bool init();
    void clear();
    void drawSnake(const std::vector<std::pair<int, int>>& snake);
    void drawFood(int x, int y);
    void drawGameOver(int score);
    void updateScore(int score);
    void present();
    
    int getTileCount() const { return tileCount; }
    SDL_Renderer* getRenderer() const { return renderer; }
};

#endif // CANVAS_H