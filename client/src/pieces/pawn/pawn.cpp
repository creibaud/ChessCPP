#include "pawn.h"

Pawn::Pawn(PieceColor color, Coordinates coordinates) : Piece(PieceType::PAWN, color, coordinates) {
    this->direction = (color == PieceColor::WHITE) ? 1 : -1;
}

void Pawn::setPossibleAttacks() {
}

void Pawn::setPossibleMoves() {
    for (std::vector<Coordinates*>::size_type i = 0; i < this->possibleMoves.size(); i++) {
        delete this->possibleMoves[i];
        delete this->possibleMovesShape[i];
    }
    this->possibleMoves.clear();
    this->possibleMovesShape.clear();

    std::string coords = this->coordinates.getCoords();
    coords[1] += this->direction;
    
    if (coords[1] >= '1' && coords[1] <= '8') {
        Coordinates* newCoords = new Coordinates(coords);

        sf::CircleShape* shape = new sf::CircleShape();
        shape->setFillColor(COLOR_POSSIBLE_MOVE);

        this->possibleMoves.push_back(newCoords);
        this->possibleMovesShape.push_back(shape);
    }
}