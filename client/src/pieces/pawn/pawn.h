#ifndef PAWN_H
#define PAWN_H

#include "../piece.h"

class Pawn : public Piece {
    private:
        int direction;
        
    public:
        Pawn(PieceColor color, Coordinates coordinates);

        void setPossibleAttacks(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) override;
        void setPossibleMoves(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces) override;

        ~Pawn() override;
};

#endif // PAWN_H