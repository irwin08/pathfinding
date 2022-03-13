#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "map.h"

class Gameloop {

public:

    Gameloop(int size_x, int size_y, std::string title);

    void run();


private:

    void processInput();
    void update();
    void render();

    sf::RenderWindow window;
    bool running;
    bool mouse_down;
    Map map;

};

#endif