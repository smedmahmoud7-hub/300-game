#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

#define MAX_FRAMES 6

typedef struct {
    SDL_Texture *frames[MAX_FRAMES];
    SDL_Texture *attackFrames[MAX_FRAMES];

    SDL_Rect rect;
    float x, y;
    float speed;

    int directionX, directionY;

    int currentFrame;
    int frameDelay;

    int isAttacking;
    int attackFrame;

    int health; // 0 → 3
} Entity;

void bar_de_vie(SDL_Renderer *renderer, Entity *enemy);
void animation(Entity *enemy);
void bar_de_vie(SDL_Renderer *renderer, Entity *enemy);
void initialisation(SDL_Window **window, SDL_Renderer **renderer, Entity *enemy, const char *folder);
void affichage_enemy(SDL_Renderer *renderer, Entity *enemy);
#endif
