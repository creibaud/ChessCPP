#ifndef CELL_H
#define CELL_H

#include "../coordinates/coordinates.h"
#include "../includes/colors.h"

class Cell {
    private:
        Coordinates coordinates;
        sf::RectangleShape shape;
        sf::Color color;
    
    public:
        Cell();

        void setCoordinates(const Coordinates &coordinates);
        void setSize(const int size, const sf::Vector2f &boardPos, bool isPlayerWhite);

        Coordinates getCoordinates() const;
        sf::Vector2f getPosition() const;
        sf::RectangleShape getShape() const;

        void render(sf::RenderWindow &window);
};

#endif // CELL_H