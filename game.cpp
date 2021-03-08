
#include "game.h"

#define grid_coor(x) PIXEL_WIDTH *x + WALL_THICKNESS

std::random_device device;
std::mt19937 generator(device());
std::uniform_int_distribution<int> distribution(0, GRID_HEIGHT - 1);

short Food::foodCount = 0;

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

Game::Game()
{
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize SDL" << std::endl;
        return;
    }

    // Init window and renderer
    window = SDL_CreateWindow(
        "Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_OPENGL);

    if (!window)
    {
        std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
        return;
    }
    else
    {
        renderer = SDL_CreateRenderer(window, -1, 0);
    }

    // Init wall rect
    wallsRect = createRect(
        WALL_THICKNESS, WALL_THICKNESS,
        SCREEN_HEIGHT - 2 * WALL_THICKNESS,
        SCREEN_WIDTH - 2 * WALL_THICKNESS);

    // Textures
    snakeBodyTexture = loadBMPTexture("resources/snake_body.bmp", renderer);
    snakeRoundingTexture = loadBMPTexture("resources/snake_rounding.bmp", renderer);
    snakeHeadTexture = loadBMPTexture("resources/snake_head.bmp", renderer);
    foodTexture = loadBMPTexture("resources/food.bmp", renderer);
    snakeTailTexture = loadBMPTexture("resources/snake_end.bmp", renderer);

    // Initialze snake
    snake.snakeHead.texture = snakeHeadTexture;
    snake.snakeHead.rect = createRect(
        grid_coor(5), grid_coor(5), PIXEL_WIDTH, PIXEL_WIDTH);
    snake.snakeHead.rotation = 0;
    snake.vx = 0;
    snake.vy = 0;

    food.rect = createRect(grid_coor(3), grid_coor(2), PIXEL_WIDTH, PIXEL_WIDTH);
    food.texture = foodTexture;
}

Game::~Game()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    std::cout << "CLOSING GAME" << std::endl;
}

void Game::drawBackground()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 100, 30, 30, 0);
    SDL_RenderFillRect(renderer, &wallsRect);
}

void Game::drawSnake()
{
    if (SDL_RenderCopyEx(renderer,
                         snake.snakeHead.texture,
                         NULL, &snake.snakeHead.rect, snake.snakeHead.rotation, NULL, SDL_FLIP_NONE) != 0)
    {
        std::cout << "Snake surface blit failed: " << SDL_GetError() << std::endl;
    }

    std::vector<SnakePart>::iterator it;
    for (it = snake.snakeBody.begin(); it != snake.snakeBody.end(); it++)
    {
        if (SDL_RenderCopyEx(renderer,
                             it->texture,
                             NULL, &it->rect, it->rotation, NULL, SDL_FLIP_NONE) != 0)
        {
            std::cout << "Snake surface blit failed: " << SDL_GetError() << std::endl;
        }
    }
}
void Game::drawFood()
{
    if (SDL_RenderCopy(renderer,
                       food.texture,
                       NULL, &food.rect) != 0)
    {
        std::cout << "Snake surface blit failed: " << SDL_GetError() << std::endl;
    }
}

bool Game::isAlive()
{
    // Wall collision detection
    if (snake.snakeHead.rect.x < grid_coor(0) || snake.snakeHead.rect.y < grid_coor(0) || snake.snakeHead.rect.x > grid_coor(GRID_LENGTH) || snake.snakeHead.rect.y > grid_coor(GRID_HEIGHT))
    {
        return true;
    }
    // Snake body/Snake haead collision
    std::vector<SnakePart>::iterator it;
    for (it = snake.snakeBody.begin(); it != snake.snakeBody.end(); it++)
    {
        if (isCollision(snake, *it))
        {
            std::cout << "DEAD!" << std::endl;
            return true;
        }
    }

    return false;
}

void Game::update(bool foodCollision)
{

    SnakePart prevSnakehead = snake.snakeHead;

    // Move snake head
    snake.snakeHead.rect.x += snake.vx * PIXEL_WIDTH;
    snake.snakeHead.rect.y += snake.vy * PIXEL_WIDTH;

    if (foodCollision)
    {
        // Add snakepart in between head and body
        snake.addSnakePart(snakeRoundingTexture, prevSnakehead.rect.x, prevSnakehead.rect.y, prevSnakehead.rotation);
        food.rect.x = grid_coor(distribution(device));
        food.rect.y = grid_coor(distribution(device));
        Food::foodCount++;
    }
    else
    {
        std::vector<SnakePart>::reverse_iterator it;
        SnakePart prevSnakePart, currentSnakePart;

        for (it = snake.snakeBody.rbegin(); it != snake.snakeBody.rend(); it++)
        {
            if (it == snake.snakeBody.rbegin())
            {
                prevSnakePart = *it;
                *it = prevSnakehead;

                if (snake.snakeHead.rotation != prevSnakePart.rotation)
                {
                    it->texture = snakeRoundingTexture;
                    // it->rotation = 90;
                }
                else
                {
                    it->texture = snakeBodyTexture;
                }
            }
            else
            {
                currentSnakePart = *it;
                *it = prevSnakePart;
                prevSnakePart = currentSnakePart;
            }
        }
    }
    // Set the tail texture
    if (snake.snakeBody.size() > 0)
    {
        (snake.snakeBody.rend() - 1)->texture = snakeTailTexture;
    }
}

void Game::run()
{
    SDL_Event event;
    bool dead = false;

    int frameTime;
    int frameElapsedTime;

    frameTime = SDL_GetTicks();

    while (!dead)
    {
        while (SDL_PollEvent(&event))
        {
            /* Keyboard event */
            if (event.type == SDL_KEYDOWN)
            {
                /* Check the SDLKey values and move change the coords */
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    if (snake.vx != 1)
                    {
                        // Update snake head
                        snake.vx = -1;
                        snake.vy = 0;
                        snake.snakeHead.rotation = 180;
                    }
                    break;
                case SDLK_RIGHT:
                    if (snake.vx != -1)
                    {
                        // Update snakehead
                        snake.vx = 1;
                        snake.vy = 0;
                        snake.snakeHead.rotation = 0;
                    }
                    break;
                case SDLK_UP:
                    if (snake.vy != 1)
                    {
                        // Update snakehead
                        snake.vx = 0;
                        snake.vy = -1;
                        snake.snakeHead.rotation = 270;
                    }
                    break;
                case SDLK_DOWN:
                    if (snake.vy != -1)
                    {
                        // Update snakehead
                        snake.vx = 0;
                        snake.vy = 1;
                        snake.snakeHead.rotation = 90;
                    }
                    break;
                default:
                    break;
                }
            }
            /* SDL_QUIT event (window close) */
            else if (event.type == SDL_QUIT)
            {
                dead = true;
            };
        }

        update(isCollision(snake, food));
        drawBackground();
        drawSnake();
        drawFood();
        SDL_RenderPresent(renderer);
        SDL_Delay(FRAME_DELAY);
        dead = isAlive();
    }
}
