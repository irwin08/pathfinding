#include <iostream>
#include "gameloop.h"

int main() {

    Gameloop game(500,600,"Path Finder");
    
    game.run();

    return 0;
}