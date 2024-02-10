#include "piece.h"

Piece::Piece(const PieceType type, const sf::Color color, const sf::Vector2i position)
    : type(type), color(color), position(position) 
{
    std::string *path = new std::string("assets/pieces/");

    if (this->color == sf::Color::Black)
        path->append("black/");
    else
        path->append("white/");
    
    switch (this->type)
    {
        case PieceType::PAWN:
            path->append("pawn.png");
            break;
        case PieceType::ROOK:
            path->append("rook.png");
            break;
        case PieceType::KNIGHT:
            path->append("knight.png");
            break;
        case PieceType::BISHOP:
            path->append("bishop.png");
            break;
        case PieceType::QUEEN:
            path->append("queen.png");
            break;
        case PieceType::KING:
            path->append("king.png");
            break;
        default:
            break;
    }

    this->image.loadFromFile(*path);
    delete path;

    this->texture.loadFromImage(this->image);
    this->sprite.setTexture(this->texture);
}

void Piece::draw(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}