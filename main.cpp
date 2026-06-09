#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "board.h"


int main() {
    sf::RenderWindow window(
        sf::VideoMode(1000,1000),
        "game of life"
    );

    int lx = 1000;
    int ly = 1000;

    float cellSize = 10.f;

    int width = lx / cellSize;
    int height = ly / cellSize;

    Board board(width, height, cellSize);
    bool running = false;
    bool paint = false;
    sf::Clock clock;
    float dt = 100.f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Space)
            {
                running = !running;
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                paint = true;
            }
            if (event.type == sf::Event::MouseButtonReleased &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                paint = false;
            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::W)
            {
                dt *= 0.9f;
            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::S)
            {
                dt *= 1.1f;
            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::R)
            {
                dt = 100.f;
            }
            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape)
            {
               board.allWhite();
               running = false; 
            }

        }
        sf::Vector2i mouse = sf::Mouse::getPosition(window);

        if (paint && mouse.x >= 0 && mouse.x < lx &&
            mouse.y >= 0 && mouse.y < ly)
        {
            board.setBoard(mouse.x / cellSize, mouse.y / cellSize);
        }

        if (running && clock.getElapsedTime().asMilliseconds() >= dt)
        {
            board.update();
            clock.restart();
        }

        window.clear();
        board.draw(window);
        window.display();
    }

    return 0;
}