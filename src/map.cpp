#include "map.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ranges>

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


void Map::click_start(sf::Vector2i pos) {
    int x_cell = (pos.x/this->cell_size);
    int y_cell = (pos.y/this->cell_size);

    std::cout << "CLICKED cell x: " << x_cell << ", y: " << y_cell << std::endl;

    if((x_cell < size) && (x_cell >= 0) && (y_cell < size) && (y_cell >= 0)) {
        //grid[x_cell][y_cell] = node_type::WALL;
        grid[start.first][start.second] = node_type::EMPTY;

        start = std::pair(x_cell, y_cell);

        grid[start.first][start.second] = node_type::START;
    }
}

void Map::click_end(sf::Vector2i pos) {
    int x_cell = (pos.x/this->cell_size);
    int y_cell = (pos.y/this->cell_size);

    std::cout << "CLICKED cell x: " << x_cell << ", y: " << y_cell << std::endl;

    if((x_cell < size) && (x_cell >= 0) && (y_cell < size) && (y_cell >= 0)) {
        //grid[x_cell][y_cell] = node_type::WALL;
        grid[end.first][end.second] = node_type::EMPTY;

        end = std::pair(x_cell, y_cell);

        grid[end.first][end.second] = node_type::END;
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
                case node_type::EXPLORED:
                    rect.setFillColor(sf::Color::Red);
                    break;
                case node_type::START:
                    rect.setFillColor(sf::Color(50,50,50));
                    break;
                case node_type::END:
                    rect.setFillColor(sf::Color(100,100,100));
                    break;
                case node_type::PATH:
                    rect.setFillColor(sf::Color(170,0,100));
                    break;
            }

            

            render_texture.draw(rect);
            render_texture.display();
        }
    }

    sf::Sprite grid_sprite(render_texture.getTexture());
    window.draw(grid_sprite);
}


std::vector<std::pair<int,int>> Map::adjacent_nodes(std::pair<int,int> node) {
    std::vector<std::pair<int,int>> adjacent;

    //check left
    if(0 <= (node.first-1)) {
        //check hard left
        adjacent.push_back(std::pair<int,int>((node.first - 1), node.second));
        //check left-up
        if(0 <= (node.second-1))
            adjacent.push_back(std::pair<int,int>((node.first - 1), (node.second - 1)));
        //check left-down
        if((node.second+1) < this->size)
            adjacent.push_back(std::pair<int,int>((node.first - 1), (node.second + 1)));
    }
    //check right
    if((node.first+1) < this->size) {
        //check hard right
        adjacent.push_back(std::pair<int,int>((node.first + 1), node.second));
        //check right-up
        if(0 <= (node.second-1))
            adjacent.push_back(std::pair<int,int>((node.first + 1), (node.second - 1)));
        //check right-down
        if((node.second+1) <= this->size)
            adjacent.push_back(std::pair<int,int>((node.first + 1), (node.second + 1)));
    }

    //check hard up
    if(0 <= (node.second - 1))
        adjacent.push_back(std::pair<int,int>(node.first, (node.second - 1)));
    //check hard down
    if((node.second + 1) < this->size)
        adjacent.push_back(std::pair<int,int>(node.first, (node.second + 1)));

    std::vector<std::pair<int,int>> adjacent_no_walls = {};

    for(auto node : adjacent) {
        if(grid[node.first][node.second] != node_type::WALL)
            adjacent_no_walls.push_back(node);
    }


    return adjacent_no_walls;
}


bool Map::BFS(std::pair<int,int> start, std::pair<int,int> end, std::vector<std::pair<int,int>> &explored, std::map<std::pair<int,int>, std::pair<int,int>> &parent_map) {


    if(start == end)
        return true;

    explored.push_back(start);

    auto adj = adjacent_nodes(start);

    std::cout << "x: " << start.first << " y: " << start.second << std::endl;

    auto adjacent_unexplored = std::ranges::filter_view(adj, [&](auto pair){ return (std::find(explored.begin(), explored.end(), pair) == explored.end()); });


    for(auto adj_node : adjacent_unexplored) {
        parent_map.insert({adj_node, start});
        if(BFS(adj_node, end, explored, parent_map)) {
            return true;
        }
    }

    return false;
}


std::vector<std::pair<int,int>> Map::path_find() {
    std::vector<std::pair<int, int>> explored = {};
    std::map<std::pair<int,int>, std::pair<int,int>> parents_map = {};


    this->BFS(start, end, explored, parents_map);

    for(auto pair : explored) {
        grid[pair.first][pair.second] = node_type::EXPLORED;
    }

    bool found_parent = false;

    auto node = end;

    std::vector<std::pair<int,int>> path = {node};

    while(!found_parent) {
        if(node == start) {
            found_parent = true;
            break;
        }

        node = parents_map.at(node);
        grid[node.first][node.second] = node_type::PATH;
    }

    return path;
}