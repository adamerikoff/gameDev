#include <stdio.h>

#include "engine/engine.h"

int main() {
    printf("Starting....\n");

    PhotonForgeMap* map = initializeMap(MAP_COLS, MAP_ROWS);
    PhotonForgePlayer* player = initializePlayer(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 20, 20);
    PhotonForgeEngine* engine = initializeEngine("testing engine", player, map);
    

    loopEngine(engine);

    printf("Exiting....\n");
    return 0;
}
