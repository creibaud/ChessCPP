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
        coords[0] += directions[i][0];
        coords[1] += directions[i][1];

        if (coords[0] >= 'a' && coords[0] <= 'h' && coords[1] >= '1' && coords[1] <= '8') {
            bool isValid = false;
            for (std::vector<Piece*>::iterator it = playerPieces->begin(); it != playerPieces->end(); it++) {
                if ((*it)->getCoordinates().getCoords() == coords) {
                    isValid = false;
                    break;
                }
            }

            for (std::vector<Piece*>::iterator it = enemyPieces->begin(); it != enemyPieces->end(); it++) {
                if ((*it)->getCoordinates().getCoords() == coords) {
                    isValid = true;
                    break;
                }
            }

            if (isValid) {
                sf::CircleShape* shape = new sf::CircleShape();
                shape->setFillColor(sf::Color::Transparent);
                shape->setOutlineColor(COLOR_POSSIBLE_MOVE);

                this->possibleAttacks.push_back(new Coordinates(coords));
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
        coords[0] += directions[i][0];
        coords[1] += directions[i][1];

        if (coords[0] >= 'a' && coords[0] <= 'h' && coords[1] >= '1' && coords[1] <= '8') {
            bool isValid = true;
            for (std::vector<Piece*>::iterator it = playerPieces->begin(); it != playerPieces->end(); it++) {
                if ((*it)->getCoordinates().getCoords() == coords) {
                    isValid = false;
                    break;
                }
            }

            for (std::vector<Piece*>::iterator it = enemyPieces->begin(); it != enemyPieces->end(); it++) {
                if ((*it)->getCoordinates().getCoords() == coords) {
                    isValid = false;
                    break;
                }
            }

            if (isValid) {
                sf::CircleShape* shape = new sf::CircleShape();
                shape->setFillColor(COLOR_POSSIBLE_MOVE);

                this->possibleMoves.push_back(new Coordinates(coords));
                this->possibleMovesShape.push_back(shape);
            }
        }
    }
}