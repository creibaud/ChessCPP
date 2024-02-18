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

        sf::Image image;
        sf::Texture texture;
        sf::Sprite sprite;
        sf::RectangleShape shape;

        bool selected;

    protected:
        float cellSize;
        sf::Vector2f position;
        bool isPlayerWhite;

        PieceColor color;
        Coordinates coordinates;
        std::vector<Coordinates*> possibleAttacks;
        std::vector<Coordinates*> possibleMoves;
        std::vector<sf::CircleShape*> possibleAttacksShape;
        std::vector<sf::CircleShape*> possibleMovesShape;
    
    public:
        Piece(PieceType type, PieceColor color, Coordinates coordinates);

        void setCoordinates(Coordinates coordinates);
        virtual void setPossibleAttacks();
        virtual void setPossibleMoves();
        void setSelected(bool selected);
        
        PieceType getType() const;
        PieceColor getColor() const;
        Coordinates getCoordinates() const;
        sf::Sprite getSprite() const;
        std::vector<Coordinates*> getPossibleAttacks() const;
        std::vector<Coordinates*> getPossibleMoves() const;

        bool isHovered(sf::Vector2i mousePos) const;
        void update(float cellSize, sf::Vector2f position, bool isPlayerWhite);

        void renderPossibleAttacks(sf::RenderWindow &window);
        void renderPossibleMoves(sf::RenderWindow &window);
        void render(sf::RenderWindow &window);
};

#endif // PIECE_H