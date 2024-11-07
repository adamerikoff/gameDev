#include "engine.h"

Engine* initializeEngine(const char* title) {
    LOG_DEBUG("Initializing Engine with title: %s, width: %d, height: %d", title, WINDOW_WIDTH, WINDOW_HEIGHT);

    Engine* engine = (Engine*)malloc(sizeof(Engine));
    if (!engine) {
        fprintf(stderr, "Error allocating memory for Engine.\n");
        return NULL;
    }
    LOG_DEBUG("Allocated memory for Engine at %p", (void*)engine);

    engine->title = strdup(title);
    if (!engine->title) {
        fprintf(stderr, "Error allocating memory for engine title.\n");
        LOG_DEBUG("Freeing allocated memory for Engine due to title allocation failure.");
        free(engine);
        return NULL;
    }
    LOG_DEBUG("Allocated memory for engine title: %s at %p", engine->title, (void*)engine->title);

    engine->width = WINDOW_WIDTH;
    engine->height = WINDOW_HEIGHT;
    engine->ticksLastTime = SDL_GetTicks();

    engine->isRunning = false;
    LOG_DEBUG("SDL initialization started.");
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        LOG_DEBUG("Freeing engine title and Engine due to SDL initialization failure.");
        free(engine->title);
        free(engine);
        return NULL;
    }
    LOG_DEBUG("SDL initialized successfully.");

    engine->window = SDL_CreateWindow(
        engine->title, 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        engine->width,
        engine->height,
        SDL_WINDOW_SHOWN
    );

    if (!engine->window) {
        fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
        LOG_DEBUG("Freeing engine title and Engine due to window creation failure.");
        SDL_Quit();
        free(engine->title);
        free(engine);
        return NULL;
    }
    LOG_DEBUG("SDL window created successfully.");

    engine->renderer = SDL_CreateRenderer(engine->window, -1, 0);
    if (!engine->renderer) {
        fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
        LOG_DEBUG("Freeing engine title and Engine due to renderer creation failure.");
        SDL_DestroyWindow(engine->window);
        SDL_Quit();
        free(engine->title);
        free(engine);
        return NULL;
    }
    LOG_DEBUG("SDL renderer created successfully.");

    SDL_SetRenderDrawBlendMode(engine->renderer, SDL_BLENDMODE_BLEND);
    
    engine->isRunning = true;
    LOG_DEBUG("Engine initialized successfully. Engine is now running.");

    return engine;
}

void destroyEngine(Engine* engine) {
    if (engine) {
        LOG_DEBUG("Destroying Engine at %p.", (void*)engine);
        if (engine->renderer) {
            SDL_DestroyRenderer(engine->renderer);
            LOG_DEBUG("SDL renderer destroyed.");
        }
        if (engine->window) {
            SDL_DestroyWindow(engine->window);
            LOG_DEBUG("SDL window destroyed.");
        }
        if (engine->title) {
            LOG_DEBUG("Freeing engine title: %s at %p", engine->title, (void*)engine->title);
            free(engine->title);
        } else {
            LOG_DEBUG("Engine title is NULL, nothing to free.");
        }
        free(engine);
        LOG_DEBUG("Engine structure freed.");
    } else {
        LOG_DEBUG("Attempted to destroy a NULL engine.");
    }
}

void renderEngine(Engine* engine) {
    LOG_DEBUG("Rendering started...");
    LOG_DEBUG("Drawing color.");
    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
    SDL_RenderClear(engine->renderer);
    LOG_DEBUG("Render cleared.");
    
    if (engine->map) {
        renderMap(engine->map, engine->renderer);
    }
    if (engine->player) {
        renderPlayer(engine->player, engine->renderer);
    }
    if (engine->rays) {
        renderRays(engine->player, engine->rays, engine->renderer);
    }
    SDL_RenderPresent(engine->renderer);
    LOG_DEBUG("Render presented.");
}

void processInputEngine(Engine* engine) {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            engine->isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                engine->isRunning = false;
            }
            break;
        default:
            break;
    }
    processInputPlayer(engine->player, &event);
}

void updateEngine(Engine* engine) {
    LOG_DEBUG("Engine update started.");
    
    LOG_DEBUG("Calculating frame time to wait.");
    int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - engine->ticksLastTime);

    LOG_DEBUG("Time to wait: %d ms", timeToWait);
    if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH) {
        LOG_DEBUG("Delaying frame by %d ms to match frame rate.", timeToWait);
        SDL_Delay(timeToWait);
    } else {
        LOG_DEBUG("No delay required for this frame.");
    }

    float deltaTime = (SDL_GetTicks() - engine->ticksLastTime) / 1000.0f;
    LOG_DEBUG("Delta time for this frame: %f seconds", deltaTime);
    engine->ticksLastTime = SDL_GetTicks();
    LOG_DEBUG("Updated engine ticksLastTime to %u", engine->ticksLastTime);
    
    if (engine->player) {
        updatePlayer(engine->player, engine->map, deltaTime);
    }
    if (engine->rays) {
        castAllRays(engine->player, engine->rays, engine->map);
    }
    LOG_DEBUG("Engine update finished.");
}

void loopEngine(Engine* engine) {
    LOG_DEBUG("Entering main loop.");
    while(engine->isRunning) {
        // Main loop logic...
        processInputEngine(engine);
        updateEngine(engine);
        renderEngine(engine);
    }
    LOG_DEBUG("Exiting main loop.");
    destroyEngine(engine);
}