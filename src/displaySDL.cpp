#include "DisplaySDL.hpp"
#include <iostream>

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
        DrawCircle(renderer, foods[i].getPos().x, foods[i].getPos().y, FOOD_SIZE);
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

void drawHUD(SDL_Renderer *renderer, World world, TTF_Font *robotoBlack)
{
    SDL_Color white = {255, 255, 255, 255};
    std::string meanRadius = "Mean Radius: " + std::to_string(world.meanRadius);
    std::string meanSpeed = "Mean Speed: " + std::to_string(world.meanSpeed);
    SDL_Surface *surface = TTF_RenderText_Solid(robotoBlack, meanRadius.c_str(), white);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    // rect.w = surface->w;
    // rect.h = surface->h;
    // SDL_RenderCopy(renderer, texture, NULL, &rect);
    // SDL_FreeSurface(surface);
    // SDL_DestroyTexture(texture);
    // surface = TTF_RenderText_Solid(robotoBlack, meanSpeed.c_str(), white);
    // texture = SDL_CreateTextureFromSurface(renderer, surface);
    // rect.x = 0;
    // rect.y = 20;
    // rect.w = surface->w;
    // rect.h = surface->h;
    // SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void draw(SDL_Renderer *renderer, World world, TTF_Font *robotoBlack)
{
    drawBackground(renderer);
    drawFood(renderer, world.foods);
    drawCells(renderer, world.cells);
    drawHUD(renderer, world, robotoBlack);
    SDL_RenderPresent(renderer);
}

void Delay(float start)
{
    if(SDL_GetTicks() - start < 1000.0f/60.0f)
    {
        SDL_Delay(1000.0f/60.0f - (SDL_GetTicks() - start));
    }
}

void SDLLoop(World world, SDL_Window *window, SDL_Renderer *renderer, SDL_Event event, float dt, TTF_Font *robotoBlack)
{
    bool quit = false;
    while (!quit)
    {
        float start = SDL_GetTicks();
        eventHandler(event, quit);
        world.Update(dt);
        draw(renderer, world, robotoBlack);
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
    TTF_Font *robotoBlack = TTF_OpenFont("media/ttf/roboto/Roboto-Black.ttf", 25);
    float dt = 60.0f/1000.0f;
    SDLLoop(world, window, renderer, event, dt, robotoBlack);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}