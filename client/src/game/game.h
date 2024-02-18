#ifndef GAME_H
#define GAME_H

#include "../pieces/piece.h"
#include "../logs/logs.h"
#include "../client/client.h"
#include <vector>

class Game {
    private:
        sf::RenderWindow window;

        sf::View staticView;
        sf::View logsView;

        float logsViewPosY;
        
        Board board;
        Logs logs;

        bool isPlayerWhite;
        std::vector<std::vector<Piece*>> pieces;

        Client client;
    
    public:
        Game();
        
        void init();
        void initClient();
        void initPieces();

        void run();

        void handleEvents();
        void handleScroll(sf::Event &event);
        void handlePieceClick(sf::Event &event);

        void update();

        void render();
};

#endif // GAME_H