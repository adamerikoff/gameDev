#include "player.h"

PhotonForgePlayer* initializePlayer(int positionX, int positionY, int rectangleSize) {
    LOG_DEBUG("Initializing Player with position (%d, %d) and rectangle size %d", positionX, positionY, rectangleSize);

    PhotonForgePlayer* player = (PhotonForgePlayer*)malloc(sizeof(PhotonForgePlayer));
    if (!player) {
        fprintf(stderr, "Error allocating memory for Player struct.\n");
        return NULL;
    }
    LOG_DEBUG("Allocated memory for Player at %p", (void*)player);

    player->positionX = positionX;
    player->positionY = positionY;
    player->rectangleSize = rectangleSize;

    LOG_DEBUG("Player initialized successfully with position (%d, %d) and size %d", player->positionX, player->positionY, player->rectangleSize);

    return player;
}

void destroyPlayer(PhotonForgePlayer* player) {
    if (!player) {
        LOG_DEBUG("Attempted to destroy a NULL Player pointer.");
        return;
    }
    LOG_DEBUG("Freeing memory for Player at %p", (void*)player);
    free(player);
    LOG_DEBUG("Player memory freed.");
}

void renderPlayer(PhotonForgePlayer* player, SDL_Renderer* renderer) {
    if (!player || !renderer) {
        fprintf(stderr, "Error: Player or renderer is NULL in renderPlayer.\n");
        return;
    }

    LOG_DEBUG("Rendering player at position (%d, %d) with size %d", player->positionX, player->positionY, player->rectangleSize);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect rect = {
        .x = player->positionX,
        .y = player->positionY,
        .w = player->rectangleSize,
        .h = player->rectangleSize
    };

    if (SDL_RenderFillRect(renderer, &rect) != 0) {
        fprintf(stderr, "Error rendering player: %s\n", SDL_GetError());
        return;
    }

    LOG_DEBUG("Player rendered successfully at position (%d, %d)", player->positionX, player->positionY);
}
