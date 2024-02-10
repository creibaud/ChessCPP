#ifndef QUEEN_H
#define QUEEN_H

#include "../piece.h"

class Queen : public Piece
{
    public:
        Queen(const sf::Color color, const sf::Vector2i position);
};

#endif // QUEEN_H