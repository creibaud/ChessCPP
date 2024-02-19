#ifndef QUEEN_H
#define QUEEN_H

#include "../piece.h"

class Queen : public Piece {
    public:
        Queen(PieceColor color, Coordinates coordinates);

        void setPossibleAttacks(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) override;
        void setPossibleMoves(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) override;
};

#endif // QUEEN_H