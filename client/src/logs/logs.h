#ifndef LOGS_H
#define LOGS_H

#include <iostream>
#include <map>
#include <vector>
#include "../includes/colors.h"

class Logs {
    private:
        sf::RectangleShape shape;
        sf::RectangleShape maskTop;
        sf::RectangleShape maskBottom;
        sf::Font font;

        int fontSize;
        float windowSize;
        float maxSize;

        int actualIndex;
        std::map<int, std::vector<sf::Text*>> logsText;

    public:
        Logs();

        void addLog(const std::string &log);

        sf::RectangleShape getShape() const;
        int getFontSize() const;
        int getMaxPosY() const;

        void update(sf::Vector2f windowSize);

        void renderMask(sf::RenderWindow &window);
        void renderText(sf::RenderWindow &window);
        void render(sf::RenderWindow &window);
};

#endif // LOGS_H