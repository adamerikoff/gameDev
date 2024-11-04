#include "engine.h"

PhotonForgeEngine* initializeEngine(const char* title, int width, int height, PhotonForgePlayer* player) {
    LOG_DEBUG("Initializing PhotonForgeEngine with title: %s, width: %d, height: %d", title, width, height);

    PhotonForgeEngine* engine = (PhotonForgeEngine*)malloc(sizeof(PhotonForgeEngine));
    if (!engine) {
        fprintf(stderr, "Error allocating memory for PhotonForgeEngine.\n");
        return NULL;
    }
    LOG_DEBUG("Allocated memory for PhotonForgeEngine at %p", (void*)engine);

    engine->title = strdup(title);
    if (!engine->title) {
        fprintf(stderr, "Error allocating memory for engine title.\n");
        LOG_DEBUG("Freeing allocated memory for PhotonForgeEngine due to title allocation failure.");
        free(engine);
        return NULL;
    }
    LOG_DEBUG("Allocated memory for engine title: %s at %p", engine->title, (void*)engine->title);

    engine->width = width;
    engine->height = height;

    engine->isRunning = false;
    LOG_DEBUG("SDL initialization started.");
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        LOG_DEBUG("Freeing engine title and PhotonForgeEngine due to SDL initialization failure.");
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
        LOG_DEBUG("Freeing engine title and PhotonForgeEngine due to window creation failure.");
        SDL_Quit();
        free(engine->title);
        free(engine);
        return NULL;
    }
    LOG_DEBUG("SDL window created successfully.");

    engine->renderer = SDL_CreateRenderer(engine->window, -1, 0);
    if (!engine->renderer) {
        fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
        LOG_DEBUG("Freeing engine title and PhotonForgeEngine due to renderer creation failure.");
        SDL_DestroyWindow(engine->window);
        SDL_Quit();
        free(engine->title);
        free(engine);
        return NULL;
    }
    LOG_DEBUG("SDL renderer created successfully.");

    SDL_SetRenderDrawBlendMode(engine->renderer, SDL_BLENDMODE_BLEND);
    
    if (player) {
        LOG_DEBUG("PhotonForgePlayer is present.");
        engine->player = player;
        LOG_DEBUG("PhotonForgePlayer inside PhotonForgeEngine is set.");
    }

    engine->isRunning = true;
    LOG_DEBUG("PhotonForgeEngine initialized successfully. Engine is now running.");

    return engine;
}

void destroyEngine(PhotonForgeEngine* engine) {
    if (engine) {
        LOG_DEBUG("Destroying PhotonForgeEngine at %p.", (void*)engine);
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
        LOG_DEBUG("PhotonForgeEngine structure freed.");
    } else {
        LOG_DEBUG("Attempted to destroy a NULL engine.");
    }
}

void renderEngine(PhotonForgeEngine* engine) {
    LOG_DEBUG("Rendering started...");
    LOG_DEBUG("Drawing color.");
    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
    LOG_DEBUG("Render clear.");
    SDL_RenderClear(engine->renderer);

    if (engine->player) {
        renderPlayer(engine->player, engine->renderer);
    }

    LOG_DEBUG("Render present.");
    SDL_RenderPresent(engine->renderer);
}

void processInputEngine(PhotonForgeEngine* engine) {
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
}

void setupEngine(PhotonForgeEngine* engine) {
    LOG_DEBUG("Setting up engine.");
    // Setup code here...
}

void loopEngine(PhotonForgeEngine* engine) {
    LOG_DEBUG("Entering main loop.");
    
    setupEngine(engine);

    while(engine->isRunning) {
        // Main loop logic...
        processInputEngine(engine);
        renderEngine(engine);
    }

    LOG_DEBUG("Exiting main loop.");
    destroyEngine(engine);
}
