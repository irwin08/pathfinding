#include <iostream>
#include "gameloop.h"

int main() {

    Gameloop game(500,600,"Hello world");
    
    game.run();

    return 0;
}