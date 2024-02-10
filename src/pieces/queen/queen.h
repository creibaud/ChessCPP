#ifndef QUEEN_H
#define QUEEN_H

#include "../piece.h"

class Queen : public Piece
{
    public:
        Queen(const sf::Color color);
};

#endif // QUEEN_H