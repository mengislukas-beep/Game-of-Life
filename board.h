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
    std::vector<std::vector<bool>> saves;
    bool saving = false;
    

public:
    Board(int width, int height, float cellSize);
    void update();
    void draw(sf::RenderWindow& window);
    void setColor(int x, int y, sf::Color color);
    void setBoard(int x, int y);
    void detBoard(int x, int y);
    void allWhite();
    void setPatter(const std::vector<std::vector<bool>>& pattern);
    void save(int index);
    void load(int index);
    void setSaving() { saving = true; }
    void resetSaving() { saving = false; }
    bool isSaving() { return saving; }
    void randomize();
    void little_random(float p);
    void update_random(float p);

};