#include <iostream>
#include <SDL.h>

SDL_Texture *loadBMPTexture(const char *filePath, SDL_Renderer *renderer)
{
    SDL_Surface *bufferSurface = SDL_LoadBMP(filePath);
    if (bufferSurface == NULL)
    {
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, bufferSurface);
    if (texture == NULL)
    {
        std::cout << "Could not load texture. Error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(bufferSurface);
    return texture;
}

SDL_Rect createRect(short x, short y, short w, short h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    return rect;
}

bool isCollision(Snake snake, GameObject object)
{
    if (object.rect.x == snake.snakeHead.rect.x && object.rect.y == snake.snakeHead.rect.y)
    {
        return true;
    }
    return false;
}
