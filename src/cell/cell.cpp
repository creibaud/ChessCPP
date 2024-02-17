#include "cell.h"

Cell::Cell() {}

void Cell::setCoordinates(const Coordinates &coordinates) {
    this->coordinates = coordinates;
    this->shape.setFillColor(coordinates.getColor());
}

void Cell::setSize(const int size, const sf::Vector2f &boardPos) {
    this->shape.setSize(sf::Vector2f(size, size));
    this->shape.setPosition(this->coordinates.getPosition().first * size + boardPos.x, this->coordinates.getPosition().second * size + boardPos.y);
}

Coordinates Cell::getCoordinates() const {
    return this->coordinates;
}

sf::RectangleShape Cell::getShape() const {
    return this->shape;
}

void Cell::render(sf::RenderWindow &window) {
    window.draw(this->shape);
}