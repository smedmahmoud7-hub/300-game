#include "headers.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600
#define MAX_FRAMES 6

void mouvementRandom(Entity *enemy) {

    if (!enemy->isAttacking) {

        if (rand() % 100 < 2) {
            enemy->directionX = (rand() % 3) - 1;
            enemy->directionY = (rand() % 3) - 1;

            if (enemy->directionX == 0 && enemy->directionY == 0)
                enemy->directionX = 1;
        }

        enemy->x += enemy->directionX * enemy->speed;
        enemy->y += enemy->directionY * enemy->speed;
    }

    if (enemy->x < 0) enemy->x = 0;
    if (enemy->x + enemy->rect.w > WIDTH)
        enemy->x = WIDTH - enemy->rect.w;

    if (enemy->y < 0) enemy->y = 0;
    if (enemy->y + enemy->rect.h > HEIGHT)
        enemy->y = HEIGHT - enemy->rect.h;

    enemy->rect.x = (int)enemy->x;
    enemy->rect.y = (int)enemy->y;
}

void initialisation(SDL_Window **window, SDL_Renderer **renderer, Entity *enemy, const char *folder)
{
    if (!*window)
        *window = SDL_CreateWindow("Game",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT, 0);

    if (!*renderer)
        *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    char path[150];

    for (int i = 0; i < MAX_FRAMES; i++) {

        sprintf(path, "assets/%s/frame%d.png", folder, i);
        enemy->frames[i] = IMG_LoadTexture(*renderer, path);

        if (!enemy->frames[i])
            printf("Erreur: %s -> %s\n", path, IMG_GetError());

        sprintf(path, "assets/%s/attack%d.png", folder, i);
        enemy->attackFrames[i] = IMG_LoadTexture(*renderer, path);

        if (!enemy->attackFrames[i])
            printf("Erreur: %s -> %s\n", path, IMG_GetError());
    }

    enemy->x = 100;
    enemy->y = 100;
    enemy->rect.w = 80;
    enemy->rect.h = 80;

    enemy->speed = 1;

    enemy->directionX = 1;
    enemy->directionY = 0;

    enemy->currentFrame = 0;
    enemy->frameDelay = 0;

    enemy->isAttacking = 0;
    enemy->attackFrame = 0;
    enemy->health = 3;
}

void animation(Entity *enemy) {

    enemy->frameDelay++;

    if (enemy->frameDelay > 6) {
        enemy->frameDelay = 0;

        if (enemy->isAttacking) {
            enemy->attackFrame++;

            if (enemy->attackFrame >= MAX_FRAMES) {
                enemy->attackFrame = 0;
                enemy->isAttacking = 0;
            }
        } else {
            enemy->currentFrame++;

            if (enemy->currentFrame >= MAX_FRAMES)
                enemy->currentFrame = 0;
        }
    }
}

void bar_de_vie(SDL_Renderer *renderer, Entity *enemy) {

    SDL_Rect bar = {
        enemy->rect.x,
        enemy->rect.y - 10,
        enemy->rect.w,
        6
    };

    if (enemy->health == 3)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    else if (enemy->health == 2)
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_RenderFillRect(renderer, &bar);
}

void affichage_enemy(SDL_Renderer *renderer, Entity *enemy)
{
    if (enemy->isAttacking) {
        if (enemy->attackFrames[enemy->attackFrame])
            SDL_RenderCopy(renderer,
                enemy->attackFrames[enemy->attackFrame],
                NULL,
                &enemy->rect);
    } else {
        if (enemy->frames[enemy->currentFrame]){
            SDL_RenderCopy(renderer,
                enemy->frames[enemy->currentFrame],
                NULL,
                &enemy->rect);
    }

    else
        SDL_RenderCopy(renderer,enemy->frames[enemy->currentFrame],NULL,&enemy->rect);
        }
}
