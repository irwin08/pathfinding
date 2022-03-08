#include "gameloop.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

Gameloop::Gameloop(int size_x, int size_y, std::string title) {

    window.create(sf::VideoMode(size_x, size_y), title);
    running = false;
}


void Gameloop::run() {

    running = true;

    sf::Clock clock;
    sf::Time lag;
    sf::Time MS_PER_FRAME = sf::milliseconds(16);

    while(running) {

        lag += clock.getElapsedTime();
        clock.restart();

        processInput();

        while(lag >= MS_PER_FRAME) {
            update();
            lag -= MS_PER_FRAME;
        }
        

        render();

    }

    //cleanup
    window.close();
}

void Gameloop::processInput() {
    sf::Event event;
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            running = false;
            std::cout << "Stopping..." << std::endl;
        }
    }
}

void Gameloop::update() {

}

void Gameloop::render() {
    window.clear(sf::Color::Cyan);

    
    window.display();
}