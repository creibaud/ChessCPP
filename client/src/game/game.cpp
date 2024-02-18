#include "game.h"

Game::Game() {
    this->logsViewPosY = 0;
    this->init();
}

void Game::init() {
    this->initClient();
    this->window.create(sf::VideoMode(1200, 800), "Chess");
    this->window.setFramerateLimit(60);
    this->board.init(this->isPlayerWhite);
    this->initPieces();
}

void Game::initClient() {
    std::string addr;
    std::cout << "Enter server address: ";
    std::cin >> addr;
    
    unsigned short port;
    std::cout << "Enter server port: ";
    std::cin >> port;

    this->client.connect(addr, port);

    if (this->client.getColor() == "black") {
        this->isPlayerWhite = false;
    } else if (this->client.getColor() == "white") {
        this->isPlayerWhite = true;
    }
}

void Game::initPieces() {
    this->pieces.push_back(std::vector<Piece*>());
    this->pieces.push_back(std::vector<Piece*>());

    for (int i = 0; i < 8; i++) {
        this->pieces[0].push_back(new Piece(PieceType::PAWN, PieceColor::WHITE, Coordinates(std::string(1, 'a' + i) + "2")));
        this->pieces[1].push_back(new Piece(PieceType::PAWN, PieceColor::BLACK, Coordinates(std::string(1, 'a' + i) + "7")));
    }

    this->pieces[0].push_back(new Piece(PieceType::ROOK, PieceColor::WHITE, Coordinates("a1")));
    this->pieces[0].push_back(new Piece(PieceType::KNIGHT, PieceColor::WHITE, Coordinates("b1")));
    this->pieces[0].push_back(new Piece(PieceType::BISHOP, PieceColor::WHITE, Coordinates("c1")));
    this->pieces[0].push_back(new Piece(PieceType::QUEEN, PieceColor::WHITE, Coordinates("d1")));
    this->pieces[0].push_back(new Piece(PieceType::KING, PieceColor::WHITE, Coordinates("e1")));
    this->pieces[0].push_back(new Piece(PieceType::BISHOP, PieceColor::WHITE, Coordinates("f1")));
    this->pieces[0].push_back(new Piece(PieceType::KNIGHT, PieceColor::WHITE, Coordinates("g1")));
    this->pieces[0].push_back(new Piece(PieceType::ROOK, PieceColor::WHITE, Coordinates("h1")));

    this->pieces[1].push_back(new Piece(PieceType::ROOK, PieceColor::BLACK, Coordinates("a8")));
    this->pieces[1].push_back(new Piece(PieceType::KNIGHT, PieceColor::BLACK, Coordinates("b8")));
    this->pieces[1].push_back(new Piece(PieceType::BISHOP, PieceColor::BLACK, Coordinates("c8")));
    this->pieces[1].push_back(new Piece(PieceType::QUEEN, PieceColor::BLACK, Coordinates("d8")));
    this->pieces[1].push_back(new Piece(PieceType::KING, PieceColor::BLACK, Coordinates("e8")));
    this->pieces[1].push_back(new Piece(PieceType::BISHOP, PieceColor::BLACK, Coordinates("f8")));
    this->pieces[1].push_back(new Piece(PieceType::KNIGHT, PieceColor::BLACK, Coordinates("g8")));
    this->pieces[1].push_back(new Piece(PieceType::ROOK, PieceColor::BLACK, Coordinates("h8")));
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
        this->handleScroll(event);
    }
}

void Game::handleScroll(sf::Event &event) {
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

void Game::handlePieceClick(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            for (int row = 0; row < BOARD_SIZE; row++) {
                for (int col = 0; col < BOARD_SIZE; col++) {
                    if (this->board.getCell(row, col).isClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        std::string coords = this->board.getCell(row, col).getCoordinates().getCoords();
                        std::cout << "Clicked: " << coords << std::endl;
                    }
                }
            }
        }
    }
}

void Game::update() {
    this->staticView = sf::View(sf::FloatRect(0, 0, this->window.getSize().x, this->window.getSize().y));
    this->logsView = sf::View(sf::FloatRect(sf::FloatRect(0, this->logsViewPosY, this->window.getSize().x, this->window.getSize().y)));
    this->board.update(this->staticView.getSize(), this->isPlayerWhite);
    this->logs.update(this->staticView.getSize());

    for (std::vector<std::vector<Piece*>>::iterator vector = this->pieces.begin(); vector != this->pieces.end(); vector++) {
        for (std::vector<Piece*>::iterator piece = vector->begin(); piece != vector->end(); piece++) {
            (*piece)->update(this->board.getCellSize(), this->board.getPosition(), this->isPlayerWhite);
        }
    }
}

void Game::render() {
    this->window.clear(COLOR_MAIN_BG);

    this->window.setView(this->staticView);
    this->board.render(this->window);
    this->logs.render(this->window);

    for (std::vector<std::vector<Piece*>>::iterator vector = this->pieces.begin(); vector != this->pieces.end(); vector++) {
        for (std::vector<Piece*>::iterator piece = vector->begin(); piece != vector->end(); piece++) {
            (*piece)->render(this->window);
        }
    }

    this->window.setView(this->logsView);
    this->logs.renderText(this->window);

    this->window.setView(this->staticView);
    this->logs.renderMask(this->window);

    this->window.display();
}