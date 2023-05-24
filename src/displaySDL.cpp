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


void draw(SDL_Renderer *renderer, World world)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < world.cells.size(); i++)
    {
        DrawCircle(renderer, world.cells[i].getPos().x, world.cells[i].getPos().y, CELL_SIZE);
    }
    SDL_RenderPresent(renderer);
}

void SDLLoop()
{
    bool quit = false;
    World world;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;
    float dt = 60.0f/1000.0f;
    while (!quit)
    {
        float start = SDL_GetTicks();
        eventHandler(event, quit);
        world.Update(dt);
        draw(renderer, world);

        if(SDL_GetTicks() - start < 1000.0f/60.0f)
        {
            SDL_Delay(1000.0f/60.0f - (SDL_GetTicks() - start));
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}