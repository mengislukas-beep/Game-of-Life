#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


class Board {
private:
    std::vector<bool> board;
    int width;
    int height;

    float cellSize;
    

    sf::VertexArray m_vertices;

public:
    Board(int width, int height, float cellSize);
    void update();
    void draw(sf::RenderWindow& window);
    void setColor(int x, int y, sf::Color color);
    void setBoard(int x, int y);
    void allWhite();
    void setPatter(const std::vector<std::vector<bool>>& pattern);


};