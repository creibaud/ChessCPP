#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"

class Pawn : public Piece {
    public:
        Pawn(PieceColor color, Coordinates coordinates);
        void setPossibleMoves(std::vector<std::vector<Piece*>> pieces) override;
};

#endif // PAWN_H