#include "piece.h"

Piece::Piece(PieceType type, PieceColor color, Coordinates coordinates) : type(type), color(color), coordinates(coordinates) {
    std::string path = "assets/pieces/";
    path += (color == PieceColor::WHITE) ? "white/" : "black/";

    switch (type) {
        case PieceType::PAWN:
            path += "pawn";
            break;
        case PieceType::ROOK:
            path += "rook";
            break;
        case PieceType::KNIGHT:
            path += "knight";
            break;
        case PieceType::BISHOP:
            path += "bishop";
            break;
        case PieceType::QUEEN:
            path += "queen";
            break;
        case PieceType::KING:
            path += "king";
            break;
        default:
            break;
    }

    path += ".png";

    if(!this->image.loadFromFile(path)) {
        std::cerr << "Error loading image" << std::endl;
    }

    if (!this->texture.loadFromImage(this->image)) {
        std::cerr << "Error loading texture" << std::endl;
    }

    this->sprite.setTexture(this->texture);
}

void Piece::setCoordinates(Coordinates coordinates){
    this->coordinates = coordinates;
}

void Piece::setPossibleMoves() {
    this->possibleMoves.clear();
}

PieceType Piece::getType() const {
    return this->type;
}

PieceColor Piece::getColor() const {
    return this->color;
}

Coordinates Piece::getCoordinates() const {
    return this->coordinates;
}

sf::Sprite Piece::getSprite() const {
    return this->sprite;
}

bool Piece::isHovered(sf::Vector2i mousePos) const {
    return this->sprite.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

void Piece::update(float cellSize, sf::Vector2f position, bool isPlayerWhite) {
    this->sprite.setScale(cellSize / this->texture.getSize().x, cellSize / this->texture.getSize().y);
    this->sprite.setPosition(position.x + this->coordinates.getPosition(isPlayerWhite).first * cellSize, position.y + this->coordinates.getPosition(isPlayerWhite).second * cellSize);
}

void Piece::render(sf::RenderWindow &window) {
    window.draw(this->sprite);
}