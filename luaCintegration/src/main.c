#include <SDL2/SDL.h>

#include "../lib/lua/src/lua.h"
#include "../lib/lua/src/lualib.h"
#include "../lib/lua/src/lauxlib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 30
#define FRAM_TIME_LENGTH (1000 / FPS)

typedef struct {
    float x;
    float y;
    float width;
    float height;
} Player;

Player player;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool is_running = false;
int last_frame_time;

bool initialize_window(void);
void setup(void);
void process_input(void);
void update(void);
void render(void);
void destroy_window(void);

int main(int argc, char* argve[]) {
    is_running = initialize_window();
    
    setup();

    while (is_running) {
        process_input();

        update();

        render();
    }
    

    return 0;
}

bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error occurred in %s\n function!", "SDL_init()");
        return false;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        fprintf(stderr, "Error occurred in %s\n function!", "SDL_CreateWindow()");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error occurred in %s\n function!", "SDL_CreateRenderer()");
        return false;
    }

    return true;
}

void setup(void) {
    player.x = 20;
    player.y = 20;
    player.width = 10;
    player.height = 10;
}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT: {
            is_running = false;
            break;
        }
        case SDL_KEYDOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                is_running = false;
                break;
            }
        }
    
    default:
        break;
    }
}

void update(void) {
    int current_time = SDL_GetTicks();
    if (!SDL_TICKS_PASSED(current_time, last_frame_time + FRAM_TIME_LENGTH)) {
        int time_to_wait = (last_frame_time + FRAM_TIME_LENGTH) - current_time;
        SDL_Delay(time_to_wait);
    }
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();


    player.x += 100 * delta_time;
    player.y += 100 * delta_time;
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect player_rect = {
        (int)player.x, 
        (int)player.y, 
        (int)player.width, 
        (int)player.height
    };
    SDL_RenderFillRect(renderer, &player_rect);

    SDL_RenderPresent(renderer);
}

void destroy_window(void) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}