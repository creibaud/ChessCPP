#include "game.h"

Game::Game() {
    this->window.create(sf::VideoMode(800, 800), "Chess");
    this->window.setFramerateLimit(60);
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
    }
}

void Game::update() {
    this->window.setView(sf::View(sf::FloatRect(0, 0, this->window.getSize().x, this->window.getSize().y)));
    this->board.update(sf::Vector2f(this->window.getSize()));
}

void Game::render() {
    this->window.clear();
    this->board.render(this->window);
    this->window.display();
}