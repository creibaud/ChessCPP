#include "game.h"

Game::Game() {
    if (!this->cursorArrow.loadFromSystem(sf::Cursor::Arrow)) {
        std::cout << "[!] Can't load cursor arrow" << std::endl;
    }

    if (!this->cursorHand.loadFromSystem(sf::Cursor::Hand)) {
        std::cout << "[!] Can't load cursor hand" << std::endl;
    }

    this->logsViewPosY = 0;
    this->init();

    this->selectedPiece = nullptr;
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
        this->isClientTurn = false;
    } else if (this->client.getColor() == "white") {
        this->isPlayerWhite = true;
        this->isClientTurn = true;
    }

    this->client.run();
}

void Game::initPieces() {
    std::vector<Piece*> *whitePieces = new std::vector<Piece*>();
    std::vector<Piece*> *blackPieces = new std::vector<Piece*>();

    for (int i = 0; i < 8; i++) {
        whitePieces->push_back(new Piece(PieceType::PAWN, PieceColor::WHITE, Coordinates(std::string(1, 'a' + i) + "2")));
        blackPieces->push_back(new Piece(PieceType::PAWN, PieceColor::BLACK, Coordinates(std::string(1, 'a' + i) + "7")));
    }

    whitePieces->push_back(new Piece(PieceType::ROOK, PieceColor::WHITE, Coordinates("a1")));
    whitePieces->push_back(new Piece(PieceType::KNIGHT, PieceColor::WHITE, Coordinates("b1")));
    whitePieces->push_back(new Piece(PieceType::BISHOP, PieceColor::WHITE, Coordinates("c1")));
    whitePieces->push_back(new Piece(PieceType::QUEEN, PieceColor::WHITE, Coordinates("d1")));
    whitePieces->push_back(new Piece(PieceType::KING, PieceColor::WHITE, Coordinates("e1")));
    whitePieces->push_back(new Piece(PieceType::BISHOP, PieceColor::WHITE, Coordinates("f1")));
    whitePieces->push_back(new Piece(PieceType::KNIGHT, PieceColor::WHITE, Coordinates("g1")));
    whitePieces->push_back(new Piece(PieceType::ROOK, PieceColor::WHITE, Coordinates("h1")));

    blackPieces->push_back(new Piece(PieceType::ROOK, PieceColor::BLACK, Coordinates("a8")));
    blackPieces->push_back(new Piece(PieceType::KNIGHT, PieceColor::BLACK, Coordinates("b8")));
    blackPieces->push_back(new Piece(PieceType::BISHOP, PieceColor::BLACK, Coordinates("c8")));
    blackPieces->push_back(new Piece(PieceType::QUEEN, PieceColor::BLACK, Coordinates("d8")));
    blackPieces->push_back(new Piece(PieceType::KING, PieceColor::BLACK, Coordinates("e8")));
    blackPieces->push_back(new Piece(PieceType::BISHOP, PieceColor::BLACK, Coordinates("f8")));
    blackPieces->push_back(new Piece(PieceType::KNIGHT, PieceColor::BLACK, Coordinates("g8")));
    blackPieces->push_back(new Piece(PieceType::ROOK, PieceColor::BLACK, Coordinates("h8")));

    if (this->isPlayerWhite) {
        this->playerPieces = whitePieces;
        this->enemyPieces = blackPieces;
    } else {
        this->playerPieces = blackPieces;
        this->enemyPieces = whitePieces;
    }
}

void Game::run() {
    while (this->window.isOpen()) {
        this->mousePos = sf::Mouse::getPosition(this->window);
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
        this->handlePieceClick(event);
    }

    this->handlePieceHover();
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

void Game::handlePieceHover() {
    this->window.setMouseCursor(this->cursorArrow);
    for (std::vector<Piece*>::iterator piece = this->playerPieces->begin(); piece != this->playerPieces->end(); piece++) {
        if ((*piece)->isHovered(this->mousePos)) {
            this->window.setMouseCursor(this->cursorHand);
        }
    }
}

void Game::handlePieceClick(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            for (std::vector<Piece*>::iterator piece = this->playerPieces->begin(); piece != this->playerPieces->end(); piece++) {
                if ((*piece)->isHovered(this->mousePos)) {
                    if (this->selectedPiece == nullptr) {
                        this->selectedPiece = *piece;
                        this->selectedPiece->setSelected(true);
                    } else if (this->selectedPiece == *piece) {
                        this->selectedPiece->setSelected(false);
                        this->selectedPiece = nullptr;
                    } else {
                        this->selectedPiece->setSelected(false);
                        this->selectedPiece = *piece;
                        this->selectedPiece->setSelected(true);
                    }
                }
            }
        }
    }
}

void Game::update() {
    if (this->client.getEnemyMoves().size() > this->enemyMoves.size()) {
        this->enemyMoves = this->client.getEnemyMoves();
        std::cout << "Enemy move: " << this->enemyMoves.back() << std::endl;
        this->isClientTurn = true;
    }

    this->staticView = sf::View(sf::FloatRect(0, 0, this->window.getSize().x, this->window.getSize().y));
    this->logsView = sf::View(sf::FloatRect(sf::FloatRect(0, this->logsViewPosY, this->window.getSize().x, this->window.getSize().y)));
    this->board.update(this->staticView.getSize(), this->isPlayerWhite);
    this->logs.update(this->staticView.getSize());

    for (std::vector<Piece*>::iterator piece = this->playerPieces->begin(); piece != this->playerPieces->end(); piece++) {
        (*piece)->update(this->board.getCellSize(), this->board.getPosition(), this->isPlayerWhite);
    }

    for (std::vector<Piece*>::iterator piece = this->enemyPieces->begin(); piece != this->enemyPieces->end(); piece++) {
        (*piece)->update(this->board.getCellSize(), this->board.getPosition(), this->isPlayerWhite);
    }
}

void Game::render() {
    this->window.clear(COLOR_MAIN_BG);

    this->window.setView(this->staticView);
    this->board.render(this->window);
    this->logs.render(this->window);

    for (std::vector<Piece*>::iterator piece = this->enemyPieces->begin(); piece != this->enemyPieces->end(); piece++) {
        (*piece)->render(this->window);
    }

    for (std::vector<Piece*>::iterator piece = this->playerPieces->begin(); piece != this->playerPieces->end(); piece++) {
        (*piece)->render(this->window);
    }

    this->window.setView(this->logsView);
    this->logs.renderText(this->window);

    this->window.setView(this->staticView);
    this->logs.renderMask(this->window);

    this->window.display();
}