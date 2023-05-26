#include "DisplaySDL.hpp"

void DrawCircle(SDL_Renderer *renderer, int x, int y, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}


void eventHandler(SDL_Event event, bool &quit)
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
        {
            quit = true;
        }
    }
}

void drawBackground(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void drawFood(SDL_Renderer *renderer, std::vector<Food> foods)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < foods.size(); i++)
    {
        DrawCircle(renderer, foods[i].getPos().x, foods[i].getPos().y, 5);
    }
}

void drawCells(SDL_Renderer *renderer, std::vector<Cell> cells)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < cells.size(); i++)
    {
        DrawCircle(renderer, cells[i].getPos().x, cells[i].getPos().y, cells[i].getRadius());
    }
}

void draw(SDL_Renderer *renderer, World world)
{
    drawBackground(renderer);
    drawFood(renderer, world.foods);
    drawCells(renderer, world.cells);
    SDL_RenderPresent(renderer);
}

void Delay(float start)
{
    if(SDL_GetTicks() - start < 1000.0f/60.0f)
    {
        SDL_Delay(1000.0f/60.0f - (SDL_GetTicks() - start));
    }
}

void SDLLoop(World world, SDL_Window *window, SDL_Renderer *renderer, SDL_Event event, float dt)
{
    bool quit = false;
    while (!quit)
    {
        float start = SDL_GetTicks();
        eventHandler(event, quit);
        world.Update(dt);
        draw(renderer, world);
        Delay(start);
    }
}

void SDL()
{
    SDL_Init(SDL_INIT_VIDEO);
    World world;
    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;
    float dt = 60.0f/1000.0f;
    SDLLoop(world, window, renderer, event, dt);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}