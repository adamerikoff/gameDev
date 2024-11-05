#ifndef MAP_H
#define MAP_H

#include "constants.h"

#include <stdio.h>
#include <stdint.h>

#include <SDL2/SDL.h>

typedef struct PhotonForgeMap {
    int mapWidth;
    int mapHeight;

    int** map;
} PhotonForgeMap;

extern PhotonForgeMap* initializeMap(int width, int height);
extern void generateRoom(PhotonForgeMap* map);
extern void renderMap(PhotonForgeMap* map, SDL_Renderer* renderer);
extern void destroyMap(PhotonForgeMap* map);

#endif