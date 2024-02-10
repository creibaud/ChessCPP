#ifndef KING_H
#define KING_H

#include "../piece.h"

class King : public Piece
{
    public:
        King(const sf::Color color, const sf::Vector2i position);
};

#endif // KING_H