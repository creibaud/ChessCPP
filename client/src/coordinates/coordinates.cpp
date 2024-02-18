#include "coordinates.h"

Coordinates::Coordinates() {}

Coordinates::Coordinates(const std::string &coords) {
    this->coords = coords;
    this->x = coords[0] - 'a';
    this->y = '8' - coords[1];
}

void Coordinates::setCoords(const std::string &coords) {
    this->coords = coords;
    this->x = coords[0] - 'a';
    this->y = '8' - coords[1];
}

void Coordinates::setColor(const sf::Color &color) {
    this->color = color;
}

std::string Coordinates::getCoords() const {
    return this->coords;
}

std::pair<int, int> Coordinates::getPosition(bool isPlayerWhite) const {
    if (isPlayerWhite) {
        return std::make_pair(this->x, this->y);
    } else {
        return std::make_pair(7 - this->x, 7 - this->y);
    }
}

sf::Color Coordinates::getColor() const {
    return this->color;
}