#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

typedef struct PhotonForgePlayer{
    float positionX;
    float positionY;
    float width;
    float height;

    int turnDirection;
    int walkDirection;

    float rotationAngle;
    float walkSpeed;
    float turnSpeed;

} PhotonForgePlayer;

extern PhotonForgePlayer* initializePlayer(float positionX, float positionY, float width, float height);
extern void destroyPlayer(PhotonForgePlayer* player);
extern void renderPlayer(PhotonForgePlayer* player, SDL_Renderer* renderer);
extern void updatePlayer(PhotonForgePlayer* player, float deltaTime);

#endif