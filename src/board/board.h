#ifndef BOARD_H
#define BOARD_H

#include "../cell/cell.h"

#define BOARD_SIZE 8

class Board {
    private:
        Cell cells[BOARD_SIZE][BOARD_SIZE];

        float windowSize;
        float cellSize;
        float boardSize;
        sf::Vector2f boardPosition;

    public:
        Board();

        void update(sf::Vector2f windowSize);

        void render(sf::RenderWindow &window);
};

#endif // BOARD_H