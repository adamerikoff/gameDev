#ifndef ENGINE_H
#define ENGINE_H

#ifdef DEBUG
#define LOG_DEBUG(msg, ...) fprintf(stderr, "DEBUG: " msg "\n", ##__VA_ARGS__)
#else
#define LOG_DEBUG(msg, ...)
#endif


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

typedef struct PhotonForgeEngine{
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    char* title;
    int   width;
    int   height;
} PhotonForgeEngine;

extern PhotonForgeEngine* initializeEngine(const char* title, int width, int height);
extern void destroyEngine(PhotonForgeEngine* engine);

extern void renderEngine(PhotonForgeEngine* engine);
extern void updateEngine(PhotonForgeEngine* engine);

extern void processInputEngine(PhotonForgeEngine* engine);

extern void setupEngine(PhotonForgeEngine* engine);
extern void loopEngine(PhotonForgeEngine* engine);

#endif

