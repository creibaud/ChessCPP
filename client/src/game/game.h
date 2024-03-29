#ifndef GAME_H
#define GAME_H

#include "../pieces/pawn/pawn.h"
#include "../pieces/rook/rook.h"
#include "../pieces/knight/knight.h"
#include "../pieces/bishop/bishop.h"
#include "../pieces/queen/queen.h"
#include "../pieces/king/king.h"
#include "../logs/logs.h"
#include "../client/client.h"
#include <vector>

class Game {
    private:
        sf::RenderWindow window;
        sf::Vector2i mousePos;
        sf::Cursor cursorArrow;
        sf::Cursor cursorHand;

        sf::View staticView;
        sf::View logsView;

        float logsViewPosY;
        
        Board board;
        Logs logs;

        bool isPlayerWhite;
        std::vector<Piece*> *playerPieces;
        std::vector<Piece*> *enemyPieces;
        Piece *selectedPiece;

        std::vector<std::string> enemyMoves;

        Client client;
        bool isClientTurn;
    
    public:
        Game();
        
        void init();
        void initClient();
        void initPieces();

        void run();

        void handleEvents();
        void handleScroll(sf::Event &event);
        void handlePieceHover();
        void handlePieceClick(sf::Event &event);
        void handlePieceClickMove(sf::Event &event);

        void update();

        void render();
};

#endif // GAME_H