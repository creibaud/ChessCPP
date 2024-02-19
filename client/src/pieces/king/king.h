#ifndef KING_H
#define KING_H

#include "../piece.h"

class King : public Piece {
    public:
        King(PieceColor color, Coordinates coordinates);

        void setPossibleAttacks(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) override;
        void setPossibleMoves(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) override;
};

#endif // KING_H