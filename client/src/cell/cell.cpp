#include "cell.h"

Cell::Cell() {}

void Cell::setCoordinates(const Coordinates &coordinates) {
    this->coordinates = coordinates;
    this->shape.setFillColor(coordinates.getColor());
}

void Cell::setSize(const int size, const sf::Vector2f &boardPos, bool isPlayerWhite) {
    this->shape.setSize(sf::Vector2f(size, size));
    this->shape.setPosition(this->coordinates.getPosition(isPlayerWhite).first * size + boardPos.x, this->coordinates.getPosition(isPlayerWhite).second * size + boardPos.y);
}

Coordinates Cell::getCoordinates() const {
    return this->coordinates;
}

sf::Vector2f Cell::getPosition() const {
    return this->shape.getPosition();
}

sf::RectangleShape Cell::getShape() const {
    return this->shape;
}

bool Cell::isClicked(const sf::Vector2f &mousePos) const {
    return this->shape.getGlobalBounds().contains(mousePos);
}

void Cell::render(sf::RenderWindow &window) {
    window.draw(this->shape);
}