#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <string>

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
        sf::Vector2i position;
        sf::Image image;
        sf::Texture texture;
        sf::Sprite sprite;
    
    public:
        Piece(const PieceType type, const sf::Color color, const sf::Vector2i position);
        void draw(sf::RenderWindow &window);
};

#endif // PIECE_H