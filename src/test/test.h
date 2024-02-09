#ifndef TEST_H
#define TEST_H

#include <SFML/Graphics.hpp>
#include <string>

class Test
{
    private:
        sf::Image m_image;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        std::string m_filename;
    public:
        Test(std::string filename);
        void display(sf::RenderWindow &window);
};

#endif // TEST_H