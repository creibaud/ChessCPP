#ifndef BISHOP_H
#define BISHOP_H

#include "../piece.h"

class Bishop : public Piece {
    public:
        Bishop(PieceColor color, Coordinates coordinates);

        void setPossibleAttacks(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) override;
        void setPossibleMoves(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) override;
};

#endif // BISHOP_H