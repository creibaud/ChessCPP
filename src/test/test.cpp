#include "test.h"

Test::Test(std::string filename) : m_filename(filename) {
    m_image.loadFromFile(filename);
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture);
}

void Test::display(sf::RenderWindow &window) {
    window.draw(m_sprite);
}