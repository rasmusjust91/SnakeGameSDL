#ifndef UTILS_H
#define UTILS_H
#include <SDL.h>
#include "objects.h"

SDL_Texture *loadBMPTexture(const char *filePath, SDL_Renderer *renderer);
SDL_Rect createRect(short x, short y, short w, short h);
bool isCollision(Snake snake, GameObject object);

#endif