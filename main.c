#include "headers.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    srand(time(NULL));

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    Entity enemy1;
    Entity enemy2;

    initialisation(&window, &renderer, &enemy1, "enemy1");
    initialisation(&window, &renderer, &enemy2, "enemy2");

    enemy2.x = 400;
    enemy2.y = 300;
    enemy2.rect.x = 400;
    enemy2.rect.y = 300;

    int running = 1;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = 0;

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                running = 0;

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
            {
                enemy1.isAttacking = 1;
                enemy1.attackFrame = 0;

                enemy2.isAttacking = 1;
                enemy2.attackFrame = 0;
            }
        }

        mouvementRandom(&enemy1);
        mouvementRandom(&enemy2);

        animation(&enemy1);
        animation(&enemy2);

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        bar_de_vie(renderer, &enemy1);
        bar_de_vie(renderer, &enemy2);

        if (enemy1.isAttacking)
{
    if (enemy1.attackFrames[enemy1.attackFrame])
        SDL_RenderCopy(renderer, enemy1.attackFrames[enemy1.attackFrame], NULL, &enemy1.rect);
}
else
{
    if (enemy1.frames[enemy1.currentFrame])
        SDL_RenderCopy(renderer, enemy1.frames[enemy1.currentFrame], NULL, &enemy1.rect);
}
        

       if (enemy2.isAttacking)
{
    if (enemy2.attackFrames[enemy2.attackFrame])
        SDL_RenderCopy(renderer, enemy2.attackFrames[enemy2.attackFrame], NULL, &enemy2.rect);
}
else
{
    if (enemy2.frames[enemy2.currentFrame])
        SDL_RenderCopy(renderer, enemy2.frames[enemy2.currentFrame], NULL, &enemy2.rect);
}

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
