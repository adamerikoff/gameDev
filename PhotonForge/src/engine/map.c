#include "map.h"

PhotonForgeMap* initializeMap(int width, int height) {
    LOG_DEBUG("Starting map initialization with width: %d and height: %d", width, height);

    // Allocate memory for the PhotonForgeMap structure
    PhotonForgeMap* map = (PhotonForgeMap*)malloc(sizeof(PhotonForgeMap));
    if (!map) {
        fprintf(stderr, "Error allocating memory for PhotonForgeMap struct.\n");
        return NULL;
    }
    LOG_DEBUG("Memory allocated for PhotonForgeMap struct at address %p", (void*)map);

    map->mapWidth = width;
    map->mapHeight = height;
    LOG_DEBUG("Map dimensions set - Width: %d, Height: %d", map->mapWidth, map->mapHeight);

    // Allocate memory for the 2D map array (int**)
    map->map = (int**)malloc(height * sizeof(int*));
    if (!map->map) {
        fprintf(stderr, "Error allocating memory for map rows.\n");
        free(map);
        return NULL;
    }
    LOG_DEBUG("Memory allocated for map row pointers (int**) at address %p", (void*)map->map);

    // Allocate each row in the 2D map array
    for (int i = 0; i < height; i++) {
        map->map[i] = (int*)malloc(width * sizeof(int));
        if (!map->map[i]) {
            fprintf(stderr, "Error allocating memory for map columns at row %d.\n", i);
            
            // Free previously allocated rows and the map structure
            for (int j = 0; j < i; j++) {
                LOG_DEBUG("Freeing memory for row %d at address %p", j, (void*)map->map[j]);
                free(map->map[j]);
            }
            free(map->map);
            free(map);
            return NULL;
        }
        LOG_DEBUG("Memory allocated for row %d at address %p", i, (void*)map->map[i]);
    }

    // Initialize the map with default values (e.g., 0 for empty tiles)
    LOG_DEBUG("Initializing map tiles to default value (0 for open space).");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            map->map[i][j] = 0;  // Default value
        }
    }
    LOG_DEBUG("Map initialized with default values (0) for all tiles.");

    generateRoom(map);

    LOG_DEBUG("Map initialized successfully with width: %d and height: %d", width, height);
    return map;
}

void generateRoom(PhotonForgeMap* map) {
    if (map == NULL || map->map == NULL) {
        fprintf(stderr, "Map or map data is NULL. Cannot generate room.\n");
        return;
    }

    int width = map->mapWidth;
    int height = map->mapHeight;
    LOG_DEBUG("Generating room with dimensions - Width: %d, Height: %d", width, height);

    // Fill the map array with walls on the edges and open space inside
    LOG_DEBUG("Filling map with walls on the edges and open space inside.");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                map->map[i][j] = 1;  // Wall
                LOG_DEBUG("Set tile at (%d, %d) to WALL", i, j);
            } else {
                map->map[i][j] = 0;  // Open space
                LOG_DEBUG("Set tile at (%d, %d) to OPEN SPACE", i, j);
            }
        }
    }

    LOG_DEBUG("Generated room with perimeter walls and open space inside. Map size: %d x %d", width, height);
}

void renderMap(PhotonForgeMap* map, SDL_Renderer* renderer) {
    if (!map || !map->map) {
        fprintf(stderr, "Map or map data is NULL. Cannot render map.\n");
        return;
    }

    LOG_DEBUG("Rendering map with dimensions - Width: %d, Height: %d", map->mapWidth, map->mapHeight);

    for (int i = 0; i < map->mapHeight; i++) {
        for (int j = 0; j < map->mapWidth; j++) {
            int tileX = j * TILE_SIZE;
            int tileY = i * TILE_SIZE;

            int tileColor = map->map[i][j] != 0 ? 255 : 0;

            SDL_SetRenderDrawColor(renderer, tileColor, tileColor, tileColor, 255);
            SDL_Rect mapTileRect = {
                tileX * MAP_SCALE_FACTOR,
                tileY * MAP_SCALE_FACTOR,
                TILE_SIZE * MAP_SCALE_FACTOR,
                TILE_SIZE * MAP_SCALE_FACTOR,
            };

            SDL_RenderFillRect(renderer, &mapTileRect);
            //LOG_DEBUG("Rendered tile at (%d, %d) with color %d", i, j, tileColor);
        }
    }
}

void destroyMap(PhotonForgeMap* map) {
    if (map == NULL) {
        LOG_DEBUG("Map is NULL. Nothing to destroy.");
        return;
    }

    LOG_DEBUG("Destroying map with dimensions - Width: %d, Height: %d", map->mapWidth, map->mapHeight);

    // Free each row in the 2D map array
    for (int i = 0; i < map->mapHeight; i++) {
        if (map->map[i] != NULL) {
            LOG_DEBUG("Freeing memory for row %d at address %p", i, (void*)map->map[i]);
            free(map->map[i]);
        }
    }

    // Free the array of row pointers
    free(map->map);
    LOG_DEBUG("Freed memory for map row pointers.");

    // Free the PhotonForgeMap structure itself
    free(map);
    LOG_DEBUG("Freed memory for PhotonForgeMap struct.");
}

bool isWall(PhotonForgeMap* map, int x, int y) {
    if (map == NULL) {
        LOG_DEBUG("Map is NULL. Cannot check for wall.");
        return true;
    }
    int indexX = x / TILE_SIZE;
    int indexY = y / TILE_SIZE;
    // Check if the provided coordinates are within the map boundaries
    if (indexX < 0 || indexX >= map->mapWidth || indexY < 0 || indexY >= map->mapHeight) {
        LOG_DEBUG("Coordinates (%d, %d) are out of bounds. Map size is %d x %d.", x, y, map->mapWidth, map->mapHeight);
        return true;
    }

    // Return true if the tile is a wall, false if it is open space
    bool isWallTile = map->map[indexY][indexX] == 1;
    LOG_DEBUG("Tile at (%d, %d) is %s.", indexX, indexY, isWallTile ? "WALL" : "OPEN SPACE");
    return isWallTile;
}
