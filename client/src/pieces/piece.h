#ifndef PIECE_H
#define PIECE_H

#include "../board/board.h"
#include <iostream>

enum class PieceType {
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

enum class PieceColor {
    WHITE,
    BLACK
};

class Piece {
    private:
        PieceType type;
        PieceColor color;
        Coordinates coordinates;

        sf::Image image;
        sf::Texture texture;
        sf::Sprite sprite;
    
    public:
        Piece(PieceType type, PieceColor color, Coordinates coordinates);

        void setCoordinates(Coordinates coordinates);
        
        PieceType getType() const;
        PieceColor getColor() const;
        Coordinates getCoordinates() const;
        sf::Sprite getSprite() const;

        void update(float cellSize, sf::Vector2f position, bool isPlayerWhite);

        void render(sf::RenderWindow &window);
};

#endif // PIECE_H