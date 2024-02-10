#ifndef BISHOP_H
#define BISHOP_H

#include "../piece.h"

class Bishop : public Piece
{
    public:
        Bishop(const sf::Color color, const sf::Vector2i position);
};

#endif // BISHOP_H