#include "rook.h"

Rook::Rook(PieceColor color, Coordinates coordinates) : Piece(PieceType::ROOK, color, coordinates) {}

void Rook::setPossibleAttacks(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) {
    for (std::vector<Coordinates*>::size_type i = 0; i < this->possibleAttacks.size(); i++) {
        delete this->possibleAttacks[i];
        delete this->possibleAttacksShape[i];
    }
    this->possibleAttacks.clear();
    this->possibleAttacksShape.clear();

    std::string coords = this->coordinates.getCoords();

    int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    for (int i = 0; i < 4; i++) {
        for (int k = 1; k <= 7; k++) {
            std::string newCoords = coords;
            newCoords[0] += directions[i][0] * k;
            newCoords[1] += directions[i][1] * k;

            if (newCoords[0] >= 'a' && newCoords[0] <= 'h' && newCoords[1] >= '1' && newCoords[1] <= '8') {
                bool isValid = true;
                for (std::vector<Piece*>::iterator it = playerPieces->begin(); it != playerPieces->end(); it++) {
                    if ((*it)->getCoordinates().getCoords() == newCoords) {
                        isValid = false;
                        break;
                    }
                }

                if (!isValid) {
                    break;
                }

                bool isEnemy = false;
                for (std::vector<Piece*>::iterator it = enemyPieces->begin(); it != enemyPieces->end(); it++) {
                    if ((*it)->getCoordinates().getCoords() == newCoords) {
                        isEnemy = true;
                        break;
                    }
                }

                if (isEnemy) {
                    sf::CircleShape* shape = new sf::CircleShape();
                    shape->setFillColor(sf::Color::Transparent);
                    shape->setOutlineColor(COLOR_POSSIBLE_MOVE);

                    this->possibleAttacks.push_back(new Coordinates(newCoords));
                    this->possibleAttacksShape.push_back(shape);
                    break;
                }
            } else {
                break;
            }
        }
    }
}

void Rook::setPossibleMoves(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) {
    for (std::vector<Coordinates*>::size_type i = 0; i < this->possibleMoves.size(); i++) {
        delete this->possibleMoves[i];
        delete this->possibleMovesShape[i];
    }
    this->possibleMoves.clear();
    this->possibleMovesShape.clear();

    std::string coords = this->coordinates.getCoords();
    
    int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    for (int i = 0; i < 4; i++) {
        for (int k = 1; k <= 7; k++) {
            std::string newCoords = coords;
            newCoords[0] += directions[i][0] * k;
            newCoords[1] += directions[i][1] * k;

            if (newCoords[0] >= 'a' && newCoords[0] <= 'h' && newCoords[1] >= '1' && newCoords[1] <= '8') {
                bool isValid = true;
                for (std::vector<Piece*>::iterator it = playerPieces->begin(); it != playerPieces->end(); it++) {
                    if ((*it)->getCoordinates().getCoords() == newCoords) {
                        isValid = false;
                        break;
                    }
                }

                for (std::vector<Piece*>::iterator it = enemyPieces->begin(); it != enemyPieces->end(); it++) {
                    if ((*it)->getCoordinates().getCoords() == newCoords) {
                        isValid = false;
                        break;
                    }
                }

                if (isValid) {
                    sf::CircleShape* shape = new sf::CircleShape();
                    shape->setFillColor(COLOR_POSSIBLE_MOVE);

                    this->possibleMoves.push_back(new Coordinates(newCoords));
                    this->possibleMovesShape.push_back(shape);
                } else {
                    break;
                }
            } else {
                break;
            }
        }
    }
}