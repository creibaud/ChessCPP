#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"

class Pawn : public Piece
{
    public:
        Pawn(const sf::Color color);
};

#endif // PAWN_H