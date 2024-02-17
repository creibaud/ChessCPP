#include "game.h"

Game::Game() {
    this->window.create(sf::VideoMode(1200, 800), "Chess");
    this->window.setFramerateLimit(60);

    this->logsViewPosY = 0;
}

void Game::run() {
    while (this->window.isOpen()) {
        this->handleEvents();
        this->update();
        this->render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window.close();
        }

        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                if (event.mouseWheelScroll.delta > 0 && this->logsViewPosY < this->logs.getMaxPosY()) {
                    this->logsViewPosY += this->logs.getFontSize();
                } else if (event.mouseWheelScroll.delta < 0 && this->logsViewPosY > 0) {
                    this->logsViewPosY -= this->logs.getFontSize();
                }
            }
        }
    }
}

void Game::update() {
    this->staticView = sf::View(sf::FloatRect(0, 0, this->window.getSize().x, this->window.getSize().y));
    this->logsView = sf::View(sf::FloatRect(sf::FloatRect(0, this->logsViewPosY, this->window.getSize().x, this->window.getSize().y)));
    this->board.update(this->staticView.getSize());
    this->logs.update(this->staticView.getSize());
}

void Game::render() {
    this->window.clear(COLOR_MAIN_BG);

    this->window.setView(this->staticView);
    this->board.render(this->window);
    this->logs.render(this->window);

    this->window.setView(this->logsView);
    this->logs.renderText(this->window);

    this->window.setView(this->staticView);
    this->logs.renderMask(this->window);

    this->window.display();
}