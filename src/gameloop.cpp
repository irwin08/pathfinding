#include "gameloop.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "map.h"

Gameloop::Gameloop(int size_x, int size_y, std::string title) : map(Map((size_x/5), 5)){

    mouse_down = false;
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

        while(lag >= MS_PER_FRAME) {
            processInput();
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
        else if(event.type == sf::Event::KeyReleased) {
            if(event.key.code == sf::Keyboard::Enter) {
                std::cout << "Starting pathfinding..." << std::endl;
                map.path_find();
            }

        }
        else if((event.type == sf::Event::MouseButtonPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift   ))) {
            auto pos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
            auto pos_normalized = sf::Vector2i(window.mapPixelToCoords(pos));
            std::cout << pos.x << ", " << pos.y << std::endl;
            std::cout << pos_normalized.x << ", " << pos_normalized.y << std::endl;
            map.click_start(pos_normalized);
        }
        else if((event.type == sf::Event::MouseButtonPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt   ))) {
            auto pos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
            auto pos_normalized = sf::Vector2i(window.mapPixelToCoords(pos));
            std::cout << pos.x << ", " << pos.y << std::endl;
            std::cout << pos_normalized.x << ", " << pos_normalized.y << std::endl;
            map.click_end(pos_normalized);
        }
        else if((event.type == sf::Event::MouseButtonPressed)) {
            
            mouse_down = true;

            auto pos = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
            auto pos_normalized = sf::Vector2i(window.mapPixelToCoords(pos));
            std::cout << pos.x << ", " << pos.y << std::endl;
            std::cout << pos_normalized.x << ", " << pos_normalized.y << std::endl;
            map.click(pos_normalized);
            
        }
        else if((event.type == sf::Event::MouseMoved) && mouse_down) {
            auto pos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
            auto pos_normalized = sf::Vector2i(window.mapPixelToCoords(pos));
            std::cout << pos.x << ", " << pos.y << std::endl;
            std::cout << pos_normalized.x << ", " << pos_normalized.y << std::endl;
            map.click(pos_normalized);
        }
        else if(event.type == sf::Event::MouseButtonReleased) {
            mouse_down = false;
        }
        
    }
    //doing this outside event system because I don't want an infinite loop of mousedown events. Just check wrt to the current frame.
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            
    }
}

void Gameloop::update() {

}

void Gameloop::render() {
    window.clear(sf::Color::Green);

    
    map.render(window);
    
    window.display();
}