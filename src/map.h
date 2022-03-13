#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SFML/Graphics.hpp>

enum class node_type {
    EMPTY,
    WALL
};

class Map {

public:
    Map(int size, int cell_size);

    void click(sf::Vector2i pos);
    void render(sf::RenderWindow &window);


private:
    std::vector<std::vector<node_type>> grid;
    int size;
    int cell_size;
};

#endif