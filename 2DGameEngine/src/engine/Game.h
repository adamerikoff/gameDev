#ifndef GAME_H
#define GAME_H

#include "includes.h"

class Game {
private:
    /* data */
public:
    Game();
    ~Game();
    void Initialize();
    void Run();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();
};

#endif
