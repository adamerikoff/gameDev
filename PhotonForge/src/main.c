#include <stdio.h>

#include "engine/engine.h"

#define WIDTH 800
#define HEIGHT 600

int main() {
    printf("Starting....\n");

    PhotonForgePlayer* player = initializePlayer(20, 20, 30);
    PhotonForgeEngine* engine = initializeEngine("testing engine", WIDTH, HEIGHT, player);
    

    loopEngine(engine);

    printf("Exiting....\n");
    return 0;
}
