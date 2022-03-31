#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SFML/Graphics.hpp>

enum class node_type {
    EMPTY,
    WALL,
    EXPLORED,
    START,
    END,
    PATH
};

class Map {

public:
    Map(int size, int cell_size);

    void click(sf::Vector2i pos);
    void click_start(sf::Vector2i pos);
    void click_end(sf::Vector2i pos);

    void render(sf::RenderWindow &window);

    bool BFS(std::pair<int,int> start, std::pair<int,int> end, std::vector<std::pair<int,int>> &explored, std::map<std::pair<int,int>, std::pair<int,int>> &parent_map);

    std::vector<std::pair<int,int>> path_find();


private:
    std::vector<std::vector<node_type>> grid;
    int size;
    int cell_size;

    std::pair<int,int> start;
    std::pair<int,int> end;


    std::vector<std::pair<int,int>> adjacent_nodes(std::pair<int,int> node);
};

#endif