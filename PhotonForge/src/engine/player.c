#include "player.h"

PhotonForgePlayer* initializePlayer(float positionX, float positionY, float width, float height) {
    LOG_DEBUG("Initializing Player with position (%f, %f) and rectangle size w:%f, h:%f", positionX, positionY, width, height);

    PhotonForgePlayer* player = (PhotonForgePlayer*)malloc(sizeof(PhotonForgePlayer));
    if (!player) {
        fprintf(stderr, "Error allocating memory for Player struct.\n");
        return NULL;
    }
    LOG_DEBUG("Allocated memory for Player at %p", (void*)player);

    player->positionX = positionX;
    player->positionY = positionY;
    player->width = width;
    player->height = height;

    LOG_DEBUG("Player initialized successfully with position (%f, %f) and rectangle size w:%f, h:%f", positionX, positionY, width, height);

    return player;
}

void setupPlayer() {

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
        LOG_DEBUG("renderPlayer called with NULL parameter(s): player: %p, renderer: %p", (void*)player, (void*)renderer);
        return;
    }

    LOG_DEBUG("Rendering player at position (%f, %f) with rectangle size w:%f, h:%f", player->positionX, player->positionY, player->width, player->height);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_Rect rect = {
        .x = player->positionX,
        .y = player->positionY,
        .w = player->width,
        .h = player->height
    };

    if (SDL_RenderFillRect(renderer, &rect) != 0) {
        fprintf(stderr, "Error rendering player: %s\n", SDL_GetError());
        LOG_DEBUG("Failed to render player at position (%f, %f)", player->positionX, player->positionY);
        return;
    }

    LOG_DEBUG("Player rendered successfully at position (%f, %f)", player->positionX, player->positionY);
}

void updatePlayer(PhotonForgePlayer* player, float deltaTime) {
    if (!player) {
        LOG_DEBUG("Attempted to update a NULL Player pointer.");
        return;
    }

    LOG_DEBUG("Updating player position. Current position: (%f, %f), deltaTime: %f", player->positionX, player->positionY, deltaTime);

    player->positionX += 5;
    player->positionY += 5;

    LOG_DEBUG("Player position updated to (%f, %f)", player->positionX, player->positionY);
}