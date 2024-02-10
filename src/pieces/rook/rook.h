#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"

class Rook : public Piece
{
    public:
        Rook(const sf::Color color, const sf::Vector2i position);
};

#endif // ROOK_H