#ifndef GAME_H
#define GAME_H

#include "../pieces/piece.h"
#include "../logs/logs.h"
#include <vector>

class Game {
    private:
        sf::RenderWindow window;

        sf::View staticView;
        sf::View logsView;

        float logsViewPosY;
        
        Board board;
        Logs logs;

        std::vector<std::vector<Piece*>> pieces;
    
    public:
        Game();

        void initPieces();

        void run();

        void handleEvents();

        void update();

        void render();
};

#endif // GAME_H