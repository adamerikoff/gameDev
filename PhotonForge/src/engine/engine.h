#ifndef ENGINE_H
#define ENGINE_H

#include "constants.h"
#include "player.h"
#include "map.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

typedef struct PhotonForgeEngine{
    unsigned int ticksLastTime;

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    char* title;
    int   width;
    int   height;

    PhotonForgePlayer* player;
    PhotonForgeMap* map;
} PhotonForgeEngine;

extern PhotonForgeEngine* initializeEngine(const char* title, PhotonForgePlayer* player, PhotonForgeMap* map);
extern void destroyEngine(PhotonForgeEngine* engine);

extern void renderEngine(PhotonForgeEngine* engine);
extern void updateEngine(PhotonForgeEngine* engine);

extern void processInputEngine(PhotonForgeEngine* engine);

extern void setupEngine(PhotonForgeEngine* engine);
extern void loopEngine(PhotonForgeEngine* engine);

#endif

