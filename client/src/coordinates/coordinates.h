#ifndef COORDINATES_H
#define COORDINATES_H

#include <SFML/Graphics.hpp>
#include <string>

class Coordinates {
    private:
        std::string coords;
        int x;
        int y;
        sf::Color color;

    public:
        Coordinates();
        Coordinates(const std::string &coords);

        void setCoords(const std::string &coords);
        void setColor(const sf::Color &color);

        std::string getCoords() const;
        std::pair<int, int> getPosition() const;
        sf::Color getColor() const;
};

#endif // COORDINATES_H