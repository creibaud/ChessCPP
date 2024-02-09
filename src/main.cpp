#include <SFML/Graphics.hpp>
#include "test/test.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Chess");

    Test test("assets/icon.png");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        test.display(window);
        window.display();
    }
    return 0;
}