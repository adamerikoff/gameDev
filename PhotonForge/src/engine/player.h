#ifndef PLAYER_H
#define PLAYER_H

#include "debug.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

typedef struct PhotonForgePlayer{
    int positionX;
    int positionY;

    int rectangleSize;
} PhotonForgePlayer;

extern PhotonForgePlayer* initializePlayer(int positionX, int positionY, int rectangleSize);
extern void destroyPlayer(PhotonForgePlayer* player);
extern void renderPlayer(PhotonForgePlayer* player, SDL_Renderer* renderer);

#endif