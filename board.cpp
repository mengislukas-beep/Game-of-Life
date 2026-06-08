#include "board.h"
#include <SFML/Graphics.hpp>

Board::Board(int width, int height, float cellSize)
    : board(width * height, false),
      width(width),
      height(height),
      cellSize(cellSize),
      m_vertices(sf::Quads, width * height * 4)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int i = (y * width + x) * 4;

            float px = x * cellSize;
            float py = y * cellSize;

            m_vertices[i + 0].position = {px, py};
            m_vertices[i + 1].position = {px + cellSize, py};
            m_vertices[i + 2].position = {px + cellSize, py + cellSize};
            m_vertices[i + 3].position = {px, py + cellSize};

            m_vertices[i + 0].color = sf::Color::White;
            m_vertices[i + 1].color = sf::Color::White;
            m_vertices[i + 2].color = sf::Color::White;
            m_vertices[i + 3].color = sf::Color::White;

            int index = y * width + x;
            board[index] = false;
        }
    }
}

void Board::draw(sf::RenderWindow& window)
{
    window.draw(m_vertices);
}
void Board::setColor(int x, int y, sf::Color color)
{
    int i = (y * width + x) * 4;

    m_vertices[i + 0].color = color;
    m_vertices[i + 1].color = color;
    m_vertices[i + 2].color = color;
    m_vertices[i + 3].color = color;
}

void Board::update()
{
    std::vector<bool> nextBoard = board;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int neighbours = 0;

            for (int dy = -1; dy <= 1; dy++)
            {
                for (int dx = -1; dx <= 1; dx++)
                {
                    if (dx == 0 && dy == 0)
                        continue;

                    int nx = (x + dx + width) % width;
                    int ny = (y + dy + height) % height;

                    int neighbourIndex = ny * width + nx;

                    if (board[neighbourIndex])
                        neighbours++;
                }
            }

            int index = y * width + x;

            if (board[index])
            {
                nextBoard[index] = neighbours == 2 || neighbours == 3;
            }
            else
            {
                nextBoard[index] = neighbours == 3;
            }
        }
    }

    board = nextBoard;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = y * width + x;

            if (board[index])
                setColor(x, y, sf::Color::Black);
            else
                setColor(x, y, sf::Color::White);
        }
    }
}

void Board::setBoard(int x, int y) {
    board[y * width + x] = true;
    setColor(x, y, sf::Color::Black);
}

void Board::allWhite() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            setColor(x, y, sf::Color::White);
            board[y * width + x] = false;
        }
    }
}

void Board::setPatter(const std::vector<std::vector<bool>>& pattern) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (pattern[y][x]) {
                setBoard(x, y);
            }
        }
    }
}