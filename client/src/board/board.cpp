#include "board.h"

Board::Board() {
    if (!this->font.loadFromFile("assets/fonts/roboto/Roboto-Medium.ttf")) {
        std::cerr << "Error: could not load font" << std::endl;
    }
}

void Board::init(bool isPlayerWhite) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Coordinates coords;
            if (isPlayerWhite) {
                coords.setCoords(std::string(1, 'a' + j) + std::string(1, '8' - i));
            } else {
                coords.setCoords(std::string(1, 'h' - j) + std::string(1, '1' + i));
            }

            if ((i + j) % 2 == 0) {
                coords.setColor(COLOR_WHITE);
            } else {
                coords.setColor(COLOR_BLACK);
            }

            this->cells[i][j].setCoordinates(coords);

            if (i == BOARD_SIZE - 1) {
                sf::Text *text = new sf::Text(coords.getCoords()[0], this->font, 20);
                if (coords.getColor() == COLOR_WHITE) {
                    text->setFillColor(COLOR_BLACK);
                } else {
                    text->setFillColor(COLOR_WHITE);
                }
                this->letters.push_back(text);
            }

            if (j == 0) {
                sf::Text *text = new sf::Text(coords.getCoords()[1], this->font, 20);
                if (coords.getColor() == COLOR_WHITE) {
                    text->setFillColor(COLOR_BLACK);
                } else {
                    text->setFillColor(COLOR_WHITE);
                }
                this->nums.push_back(text);
            }
        }
    }
}

int Board::getCellSize() const {
    return this->cellSize;
}

sf::Vector2f Board::getPosition() const {
    return this->boardPosition;
}

Cell Board::getCell(int row, int col) const {
    return this->cells[row][col];
}

void Board::update(sf::Vector2f windowSize, bool isPlayerWhite) {
    this->windowSize = static_cast<int>(std::min(windowSize.x, windowSize.y));
    this->boardSize = static_cast<int>(1.95 * this->windowSize / 3);
    this->cellSize = static_cast<int>(this->boardSize / BOARD_SIZE);
    this->boardPosition = sf::Vector2f(this->windowSize * 0.05 / 3 + windowSize.x / 2 - 3.05 * this->boardSize / 4, (windowSize.y - this->boardSize) / 2);

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            this->cells[i][j].setSize(this->cellSize, this->boardPosition, isPlayerWhite);

            if (i == BOARD_SIZE - 1) {
                this->letters[j]->setCharacterSize(this->windowSize / 55);
                this->letters[j]->setPosition(this->cells[i][j].getPosition().x + this->cellSize - 0.75 * this->letters[j]->getCharacterSize(), this->cells[i][j].getPosition().y + this->cellSize - 1.25 * this->letters[j]->getCharacterSize());
            }

            if (j == 0) {
                this->nums[i]->setCharacterSize(this->windowSize / 55);
                this->nums[i]->setPosition(this->cells[i][j].getPosition().x + 0.25 * this->nums[i]->getCharacterSize(), this->cells[i][j].getPosition().y + 0.15 * this->nums[i]->getCharacterSize());
            }
        }
    }
}

void Board::render(sf::RenderWindow &window) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            this->cells[i][j].render(window);

            if (i == BOARD_SIZE - 1) {
                window.draw(*this->letters[j]);
            }

            if (j == 0) {
                window.draw(*this->nums[i]);
            }
        }
    }
}