#ifndef PIECE_H
#define PIECE_H

#include "../includes/position.h"
#include <SFML/Graphics.hpp>

enum class PieceType
{
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

class Piece
{
    private:
        PieceType type;
        sf::Color color;
        Position pos;
        sf::Image image;
        sf::Texture texture;
        sf::Sprite sprite;
    
    public:
        Piece(const PieceType type, const sf::Color color, const Position pos);
        void draw(sf::RenderWindow &window);
};

#endif // PIECE_H