#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "Simulation.h"

#ifndef _PARAMS_
    #define ROWS 80
    #define COLS 80
    #define GENERATIONS 1000
    #define BLOCK_SIZE 10
    #define RATE 50
    #define WIN_WIDTH (BLOCK_SIZE * ROWS + ROWS - 1)
    #define WIN_HEIGHT (BLOCK_SIZE * COLS + COLS - 1)
#endif


namespace gol {

    namespace gui {

        std::vector<std::vector<sf::RectangleShape>> grid;
        sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "The Game of Life");

        void setup() {
            for (int i = 0, y = 0; i < ROWS; ++i, y += BLOCK_SIZE + 1) {
                std::vector<sf::RectangleShape> row;
                for (int j = 0, x = 0; j < COLS; ++j, x += BLOCK_SIZE + 1) {
                    sf::RectangleShape cell(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                    cell.setPosition(sf::Vector2f(x, y));
                    row.push_back(cell);
                }
                grid.push_back(row);
            }
        }

        void update(Board& board) {
            window.clear();
            for (int i = 0, y = 0; i < board.get_rows(); ++i, y += BLOCK_SIZE + 1) {
                for (int j = 0, x = 0; j < board.get_cols(); ++j, x += BLOCK_SIZE + 1) {
                    grid[i][j].setOutlineThickness(1);
                    grid[i][j].setOutlineColor(sf::Color::Black);
                    grid[i][j].setFillColor(board.get(i, j) == 0 ? 
                        sf::Color(21, 21, 21) : 
                        sf::Color::White);
                    window.draw(grid[i][j]);
                }
            }
            window.display();
        }
    }

    std::string& random_population(int r, int c) {
        srand(static_cast<unsigned int>(time(nullptr)));
        std::string* population = new std::string();
        for (uint32_t i = 0; i < r; i++) {
            for (uint32_t j = 0; j < c; j++)
                *population += rand() % 2 == 0 ? "0" : "1";
            *population += "\n";
        }
        return *population;
    }
}


int main(int argc, char const *argv[])
{
    // std::string initial = "11100\n01110\n00100\n10011\n10001\0";
    std::string initial = gol::random_population(ROWS, COLS);
    Simulation sim(ROWS, COLS, GENERATIONS, initial);
    gol::gui::setup();

    while (gol::gui::window.isOpen()) {
        sf::Event event;
        while (gol::gui::window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                gol::gui::window.close();
            }
        }
        if (!sim.isOver()) {
            gol::gui::update(sim.next());
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / RATE));
        }
    }

    return 0;
}
