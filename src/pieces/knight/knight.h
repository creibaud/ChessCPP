#ifndef KNIGHT_H
#define KNIGHT_H

#include "../piece.h"

class Knight : public Piece
{
    public:
        Knight(const sf::Color color, const sf::Vector2i position);
};

#endif // KNIGHT_H