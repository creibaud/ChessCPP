#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"

class Pawn : public Piece {
    private:
        int direction;
        
    public:
        Pawn(PieceColor color, Coordinates coordinates);
        void setPossibleAttacks() override;
        void setPossibleMoves() override;
};

#endif // PAWN_H