#ifndef GAME_H
#define GAME_H

#include "../board/board.h"
#include "../logs/logs.h"

class Game {
    private:
        sf::RenderWindow window;

        sf::View staticView;
        sf::View logsView;

        float logsViewPosY;
        
        Board board;
        Logs logs;
    
    public:
        Game();

        void run();

        void handleEvents();

        void update();

        void render();
};

#endif // GAME_H