#include "objects.h"
#include "utils.h"

void Snake::addSnakePart(SDL_Texture *texture, short x, short y, short rotation)
{
    SnakePart snakePart;
    snakePart.rect = createRect(x, y, PIXEL_WIDTH, PIXEL_WIDTH);
    snakePart.texture = texture;
    snakePart.rotation = rotation;
    snakeBody.push_back(snakePart);
}
