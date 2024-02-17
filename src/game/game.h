#ifndef GAME_H
#define GAME_H

#include "../board/board.h"

class Game {
    private:
        sf::RenderWindow window;
        Board board;
    
    public:
        Game();

        void run();

        void handleEvents();

        void update();

        void render();
};

#endif // GAME_H