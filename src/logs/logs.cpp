#include "logs.h"

Logs::Logs() {
    this->shape.setFillColor(COLOR_LOGS_BG);
    this->windowSize = 0;
    this->maxSize = 0;

    this->font.loadFromFile("assets/fonts/roboto/Roboto-Medium.ttf");
    this->fontSize = 0;

    for (int i = 0; i < 50; i++) {
        sf::Text *text = new sf::Text(std::to_string(i), this->font, 20);
        text->setFillColor(COLOR_WHITE);
        this->logsText.push_back(text);
    }
}

sf::RectangleShape Logs::getShape() const {
    return this->shape;
}

int Logs::getFontSize() const {
    return this->fontSize;
}

int Logs::getMaxPosY() const {
    return (this->logsText.size() - 1) * this->fontSize;
}

void Logs::update(sf::Vector2f windowSize) {
    this->windowSize = std::min(windowSize.x, windowSize.y);
    this->maxSize = this->windowSize / 3;
    this->shape.setSize(sf::Vector2f(this->maxSize * 0.90, 1.95 * this->maxSize));
    this->shape.setPosition(sf::Vector2f(2.05 * this->maxSize + windowSize.x / 2 - 3 * this->maxSize / 2, windowSize.y / 2 - 0.975 * this->maxSize));

    this->fontSize = this->windowSize / 40;
}

void Logs::renderMask(sf::RenderWindow &window) {
    this->maskTop.setSize(sf::Vector2f(this->shape.getSize().x, window.getSize().y));
    this->maskTop.setPosition(this->shape.getPosition().x, this->shape.getPosition().y - window.getSize().y);
    this->maskTop.setFillColor(COLOR_MAIN_BG);

    this->maskBottom.setSize(sf::Vector2f(this->shape.getSize().x, window.getSize().y));
    this->maskBottom.setPosition(this->shape.getPosition().x, this->shape.getPosition().y + this->shape.getSize().y);
    this->maskBottom.setFillColor(COLOR_MAIN_BG);

    window.draw(this->maskTop);
    window.draw(this->maskBottom);
}

void Logs::renderText(sf::RenderWindow &window) {
    for (std::vector<sf::Text*>::size_type i = 0; i < this->logsText.size(); i++) {
        this->logsText[i]->setCharacterSize(this->fontSize);
        this->logsText[i]->setPosition(this->shape.getPosition().x + this->fontSize, this->shape.getPosition().y + i * this->fontSize);
        window.draw(*this->logsText[i]);
    }
}

void Logs::render(sf::RenderWindow &window) {
    window.draw(this->shape);
}