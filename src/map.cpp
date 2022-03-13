#include "map.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Map::Map(int size, int cell_size) {
    grid = std::vector<std::vector<node_type>>(size, std::vector<node_type>(size, node_type::EMPTY));
    this->size = size;
    this->cell_size = cell_size;
}

void Map::click(sf::Vector2i pos) {
    int x_cell = (pos.x/this->cell_size);
    int y_cell = (pos.y/this->cell_size);

    std::cout << "CLICKED cell x: " << x_cell << ", y: " << y_cell << std::endl;

    if((x_cell < size) && (x_cell >= 0) && (y_cell < size) && (y_cell >= 0)) {
        grid[x_cell][y_cell] = node_type::WALL;
    }
}

void Map::render(sf::RenderWindow &window) {
    //each block will be 5x5
    int render_texture_length = this->cell_size*size;

    sf::RenderTexture render_texture;
    render_texture.create(render_texture_length, render_texture_length);

    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid.size(); j++) {
            sf::RectangleShape rect(sf::Vector2f(this->cell_size,this->cell_size));
            rect.setPosition(i*this->cell_size, j*this->cell_size);

            switch(grid[i][j]) {
                case node_type::EMPTY:
                    rect.setFillColor(sf::Color(220,220,220));
                    break;
                case node_type::WALL:
                    rect.setFillColor(sf::Color::Black);
                    break;
            }

            

            render_texture.draw(rect);
            render_texture.display();
        }
    }

    sf::Sprite grid_sprite(render_texture.getTexture());
    window.draw(grid_sprite);
}