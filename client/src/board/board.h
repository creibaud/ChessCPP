#ifndef BOARD_H
#define BOARD_H

#include "../cell/cell.h"
#include <vector>
#include <iostream>

#define BOARD_SIZE 8

class Board {
    private:
        Cell cells[BOARD_SIZE][BOARD_SIZE];

        int windowSize;
        int cellSize;
        int boardSize;
        sf::Vector2f boardPosition;

        sf::Font font;
        std::vector<sf::Text*> nums;
        std::vector<sf::Text*> letters;

    public:
        Board();

        void init(bool isPlayerWhite);

        int getCellSize() const;
        sf::Vector2f getPosition() const;

        void update(sf::Vector2f windowSize, bool isPlayerWhite);

        void render(sf::RenderWindow &window);
};

#endif // BOARD_H