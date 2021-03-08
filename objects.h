#ifndef OBJ_H
#define OBJ_H
#include <iostream>
#include <vector>
#include <string>
#include <SDL.h>
#include "constants.h"

struct GameObject
{
    SDL_Texture *texture;
    SDL_Rect rect;
};

struct Food : GameObject
{
    static short foodCount;
};

struct SnakePart : GameObject
{
    short rotation;
    bool isCurved;
};

struct Snake
{
    SnakePart snakeHead;
    std::vector<SnakePart> snakeBody;
    short vx, vy;
    void addSnakePart(SDL_Texture *texture, short x, short y, short rotation);
};

#endif