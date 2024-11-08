#include "Game.h"


Game::Game(/* args */) {
    std::cout << "Game constructor called." << std::endl;
}

Game::~Game() {
    std::cout << "Game destructor called." << std::endl;
}

void Game::Initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL!" << std::endl;
        return;
    }
    window = SDL_CreateWindow(
        "testing",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "Error creating SDL window!" << std::endl;
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer!" << std::endl;
        return;
    }
    isRunning = true;
}

void Game::Run() {
    while (isRunning) {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;
        default:
            break;
        }
    }
}

void Game::Update() {

}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    if (!renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (!window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}