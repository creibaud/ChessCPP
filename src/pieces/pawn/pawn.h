#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"

class Pawn : public Piece
{
    public:
        Pawn(const sf::Color color, const sf::Vector2i position);
};

#endif // PAWN_H