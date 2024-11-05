#define DEBUG

#ifndef CONSTANTS_H
#define CONSTANTS_H

#ifdef DEBUG
#define LOG_DEBUG(msg, ...) fprintf(stderr, "DEBUG: " msg "\n", ##__VA_ARGS__)
#else
#define LOG_DEBUG(msg, ...)
#endif

#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)

#define PI 3.14159265
#define DOUBLE_PI 6.28318530

#define TILE_SIZE 32

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FOV_ANGLE (60 * (PI / 180))
#define NUM_RAYS WINDOW_WIDTH

#define MAP_ROWS (WINDOW_HEIGHT / TILE_SIZE)
#define MAP_COLS (WINDOW_WIDTH / TILE_SIZE)
#define MAP_SCALE_FACTOR 0.3

#define PLAYER_TILE_SIZE (MAP_SCALE_FACTOR * TILE_SIZE)

#endif