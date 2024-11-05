#include <stdio.h>

#include "engine/engine.h"

int main() {
    printf("Starting....\n");

    PhotonForgeMap* map = initializeMap(MAP_COLS, MAP_ROWS);
    PhotonForgePlayer* player = initializePlayer(20, 20, PLAYER_TILE_SIZE, PLAYER_TILE_SIZE);
    PhotonForgeEngine* engine = initializeEngine("testing engine", player, map);
    

    loopEngine(engine);

    printf("Exiting....\n");
    return 0;
}
