#ifndef PIECE_H
#define PIECE_H

#include "../board/board.h"
#include "../includes/pieces.h"
#include <iostream>
#include <fstream>

class Piece {
    private:
        PieceType type;
        std::string name;

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
        virtual void setPossibleAttacks(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces);
        virtual void setPossibleMoves(std::vector<Piece*> *playerPieces, std::vector<Piece*> *enemyPieces);
        void setSelected(bool selected);
        
        std::string getName() const;
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

        virtual ~Piece();
};

#endif // PIECE_H