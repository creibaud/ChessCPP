#include "pawn.h"

Pawn::Pawn(PieceColor color, Coordinates coordinates) : Piece(PieceType::PAWN, color, coordinates) {
    this->direction = (color == PieceColor::WHITE) ? 1 : -1;
    this->firstMove = true;
}

void Pawn::setFirstMove(bool firstMove) {
    this->firstMove = firstMove;
}

void Pawn::setPossibleAttacks(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) {
    for (std::vector<Coordinates*>::size_type i = 0; i < this->possibleAttacks.size(); i++) {
        delete this->possibleAttacks[i];
        delete this->possibleAttacksShape[i];
    }
    this->possibleAttacks.clear();
    this->possibleAttacksShape.clear();

    for (int i = 0; i < 2; i++) {
        std::string coords = this->coordinates.getCoords();
        coords[0] += (i == 0) ? -1 : 1;
        coords[1] += this->direction;

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

void Pawn::setPossibleMoves(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) {
    for (std::vector<Coordinates*>::size_type i = 0; i < this->possibleMoves.size(); i++) {
        delete this->possibleMoves[i];
        delete this->possibleMovesShape[i];
    }
    this->possibleMoves.clear();
    this->possibleMovesShape.clear();

    std::string coords = this->coordinates.getCoords();

    for (int i = 0; i < 1 + (this->firstMove ? 1 : 0); i++) {
        coords[1] += this->direction;
    
        if (coords[1] >= '1' && coords[1] <= '8') {
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