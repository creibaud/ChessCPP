#include "logs.h"

Logs::Logs() {
    this->shape.setFillColor(COLOR_LOGS_BG);
    this->windowSize = 0;
    this->maxSize = 0;

    if (!this->font.loadFromFile("assets/fonts/roboto/Roboto-Medium.ttf")) {
        std::cerr << "Error: could not load font" << std::endl;
    }
    
    this->fontSize = 0;
    this->actualIndex = 1;
    sf::Text *index = new sf::Text(std::to_string(this->actualIndex), this->font, this->fontSize);
    this->logsText[this->actualIndex].emplace_back(index);
}

void Logs::addLog(const std::string &log) {
    sf::Text *text = new sf::Text();
    
    if (log[1] == 'x') {
        if (log.substr(0, 1) == std::string(1, 'P')) {
            text->setString(log.substr(3, 1) + log.substr(1, 1) + log.substr(7, 2));
        } else {
            text->setString(log.substr(0, 2) + log.substr(7, 2));
        }
    } else {
        if (log.substr(0, 1) == std::string(1, 'P')) {
            text->setString(log.substr(7, 2));
        } else {
            text->setString(log.substr(0, 1) + log.substr(7, 2));
        }
    }

    text->setFont(this->font);
    
    if (this->logsText[this->actualIndex].size() < 3) {
        this->logsText[this->actualIndex].emplace_back(text);
    } else {
        this->actualIndex++;
        sf::Text *index = new sf::Text(std::to_string(this->actualIndex), this->font, this->fontSize);
        this->logsText[this->actualIndex].emplace_back(index);
        this->logsText[this->actualIndex].emplace_back(text);
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
    for (std::map<int, std::vector<sf::Text*>>::iterator it = this->logsText.begin(); it != this->logsText.end(); ++it) {
        for (std::vector<sf::Text*>::size_type i = 0; i != it->second.size(); i++) {
            it->second[i]->setCharacterSize(this->fontSize);
            it->second[i]->setPosition(this->shape.getPosition().x + 4 * i * this->fontSize + (i == 0 ? this->fontSize : 0), this->shape.getPosition().y + (it->first - 1) * (this->fontSize + 1));
            window.draw(*it->second[i]);
        }
    }
}

void Logs::render(sf::RenderWindow &window) {
    window.draw(this->shape);
}