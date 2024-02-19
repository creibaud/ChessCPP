#ifndef ROOK_H
#define ROOK_H

#include "../piece.h"

class Rook : public Piece {
    public:
        Rook(PieceColor color, Coordinates coordinates);

        void setPossibleAttacks(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) override;
        void setPossibleMoves(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) override;
};

#endif // ROOK_H