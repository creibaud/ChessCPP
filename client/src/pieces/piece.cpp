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
    this->selected = false;
}

void Piece::setCoordinates(Coordinates coordinates){
    this->coordinates = coordinates;
}

void Piece::setPossibleAttacks() {
    this->possibleAttacksShape.clear();
    this->possibleAttacks.clear();
}

void Piece::setPossibleMoves() {
    this->possibleMovesShape.clear();
    this->possibleMoves.clear();
}

void Piece::setSelected(bool selected) {
    this->selected = selected;
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
    this->cellSize = cellSize;
    this->position = position;
    this->isPlayerWhite = isPlayerWhite;

    this->sprite.setScale(cellSize / this->texture.getSize().x, cellSize / this->texture.getSize().y);
    this->sprite.setPosition(position.x + this->coordinates.getPosition(isPlayerWhite).first * cellSize, position.y + this->coordinates.getPosition(isPlayerWhite).second * cellSize);
    this->shape.setSize(this->sprite.getGlobalBounds().getSize());
    this->shape.setPosition(this->sprite.getPosition());

    if (this->selected) {
        this->shape.setFillColor(COLOR_SELECTED);
    } else {
        this->shape.setFillColor(sf::Color::Transparent);
    }

    for (std::vector<sf::CircleShape*>::size_type i = 0; i != this->possibleAttacksShape.size(); i++) {
        this->possibleAttacksShape[i]->setRadius(this->cellSize * 0.25);
        this->possibleAttacksShape[i]->setPosition(this->position.x + this->possibleAttacks[i]->getPosition(isPlayerWhite).first * cellSize + cellSize / 2 - this->cellSize * 0.25, this->position.y + this->possibleAttacks[i]->getPosition(isPlayerWhite).second * cellSize + cellSize / 2 - this->cellSize * 0.25);
    }

    for (std::vector<sf::CircleShape*>::size_type i = 0; i != this->possibleMovesShape.size(); i++) {
        this->possibleMovesShape[i]->setRadius(this->cellSize * 0.15);
        this->possibleMovesShape[i]->setPosition(this->position.x + this->possibleMoves[i]->getPosition(isPlayerWhite).first * cellSize + cellSize / 2 - this->cellSize * 0.15, this->position.y + this->possibleMoves[i]->getPosition(isPlayerWhite).second * cellSize + cellSize / 2 - this->cellSize * 0.15);
    }
}

std::vector<Coordinates*> Piece::getPossibleAttacks() const {
    return this->possibleAttacks;
}

std::vector<Coordinates*> Piece::getPossibleMoves() const {
    return this->possibleMoves;
}

void Piece::renderPossibleAttacks(sf::RenderWindow &window) {
    for (std::vector<sf::CircleShape*>::iterator it = this->possibleAttacksShape.begin(); it != this->possibleAttacksShape.end(); ++it) {
        window.draw(**it);
    }
}

void Piece::renderPossibleMoves(sf::RenderWindow &window) {
    for (std::vector<sf::CircleShape*>::iterator it = this->possibleMovesShape.begin(); it != this->possibleMovesShape.end(); ++it) {
        window.draw(**it);
    }
}

void Piece::render(sf::RenderWindow &window) {
    window.draw(this->shape);

    if (this->selected) {
        this->renderPossibleAttacks(window);
        this->renderPossibleMoves(window);
    }

    window.draw(this->sprite);
}