#include "board.h"

Board::Board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Coordinates coords;
            coords.setCoords(std::string(1, 'a' + j) + std::string(1, '8' - i));
            if ((i + j) % 2 == 0) {
                coords.setColor(COLOR_WHITE);
            } else {
                coords.setColor(COLOR_BLACK);
            }

            this->cells[i][j].setCoordinates(coords);
        }
    }
}

void Board::update(sf::Vector2f windowSize) {
    this->windowSize = std::min(windowSize.x, windowSize.y);
    this->boardSize = 1.95 * this->windowSize / 3;
    this->cellSize = this->boardSize / BOARD_SIZE;
    this->boardPosition = sf::Vector2f(this->windowSize * 0.05 / 3 + windowSize.x / 2 - 3.05 * this->boardSize / 4, (windowSize.y - this->boardSize) / 2);

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            this->cells[i][j].setSize(this->cellSize, this->boardPosition);
        }
    }
}

void Board::render(sf::RenderWindow &window) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            this->cells[i][j].render(window);
        }
    }
}