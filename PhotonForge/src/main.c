#include <stdio.h>

#include "engine/engine.h"

#define DEBUG

#define WIDTH 800
#define HEIGHT 600

int main() {
    printf("Starting....\n");

    PhotonForgeEngine* engine = initializeEngine("testing engine", WIDTH, HEIGHT);

    loopEngine(engine);

    printf("Exiting....\n");
    return 0;
}
