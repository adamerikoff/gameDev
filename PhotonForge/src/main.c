#include <stdio.h>

#include "engine/engine.h"

int main() {
    printf("Starting....\n");
    Map* map = generateEmptyMap(MAP_ROWS, MAP_COLS);
    Player* player = initializePlayer(WINDOW_HEIGHT/2, WINDOW_WIDTH/2, TILE_SIZE, TILE_SIZE);
    Engine* engine = initializeEngine("testing engine");
    engine->player = player;
    engine->map = map;
    loopEngine(engine);    
    printf("Exiting....\n");
    return 0;
}
