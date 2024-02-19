#include "knight.h"

Knight::Knight(PieceColor color, Coordinates coordinates) : Piece(PieceType::KNIGHT, color, coordinates) {}

void Knight::setPossibleAttacks(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) {
    for (std::vector<Coordinates*>::size_type i = 0; i < this->possibleAttacks.size(); i++) {
        delete this->possibleAttacks[i];
        delete this->possibleAttacksShape[i];
    }
    this->possibleAttacks.clear();
    this->possibleAttacksShape.clear();

    std::string coords = this->coordinates.getCoords();

    int directions[8][2] = {{-1, 2}, {1, 2}, {-1, -2}, {1, -2}, {-2, 1}, {-2, -1}, {2, 1}, {2, -1}};

    for (int i = 0; i < 8; i++) {
        std::string newCoords = coords;
        newCoords[0] += directions[i][0];
        newCoords[1] += directions[i][1];

        if (newCoords[0] >= 'a' && newCoords[0] <= 'h' && newCoords[1] >= '1' && newCoords[1] <= '8') {
            bool isValid = false;
            for (std::vector<Piece*>::iterator it = playerPieces->begin(); it != playerPieces->end(); it++) {
                if ((*it)->getCoordinates().getCoords() == newCoords) {
                    isValid = false;
                    break;
                }
            }

            for (std::vector<Piece*>::iterator it = enemyPieces->begin(); it != enemyPieces->end(); it++) {
                if ((*it)->getCoordinates().getCoords() == newCoords) {
                    isValid = true;
                    break;
                }
            }

            if (isValid) {
                sf::CircleShape* shape = new sf::CircleShape();
                shape->setFillColor(sf::Color::Transparent);
                shape->setOutlineColor(COLOR_POSSIBLE_MOVE);

                this->possibleAttacks.push_back(new Coordinates(newCoords));
                this->possibleAttacksShape.push_back(shape);
            }
        }
    }
}

void Knight::setPossibleMoves(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) {
    for (std::vector<Coordinates*>::size_type i = 0; i < this->possibleMoves.size(); i++) {
        delete this->possibleMoves[i];
        delete this->possibleMovesShape[i];
    }
    this->possibleMoves.clear();
    this->possibleMovesShape.clear();

    std::string coords = this->coordinates.getCoords();
    
    int directions[8][2] = {{-1, 2}, {1, 2}, {-1, -2}, {1, -2}, {-2, 1}, {-2, -1}, {2, 1}, {2, -1}};

    for (int i = 0; i < 8; i++) {
        std::string newCoords = coords;
        newCoords[0] += directions[i][0];
        newCoords[1] += directions[i][1];

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
            }
        }
    }
}