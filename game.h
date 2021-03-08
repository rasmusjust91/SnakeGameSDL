#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
#include <vector>
#include <random>
#include "constants.h"
#include "objects.h"

class Game
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect windowRect, wallsRect;
    SDL_Texture *snakeHeadTexture, *snakeBodyTexture, *snakeRoundingTexture, *foodTexture, *snakeTailTexture;
    Snake snake;
    Food food;
    bool isAlive();
    void update(bool collision);
    void drawBackground();
    void drawSnake();
    void drawFood();

public:
    Game();
    void run();
    ~Game();
};

#endif