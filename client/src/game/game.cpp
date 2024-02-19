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
        whitePieces->push_back(new Pawn(PieceColor::WHITE, Coordinates(std::string(1, 'a' + i) + "2")));
        blackPieces->push_back(new Pawn(PieceColor::BLACK, Coordinates(std::string(1, 'a' + i) + "7")));
    }

    whitePieces->push_back(new Rook(PieceColor::WHITE, Coordinates("a1")));
    whitePieces->push_back(new Knight(PieceColor::WHITE, Coordinates("b1")));
    whitePieces->push_back(new Bishop(PieceColor::WHITE, Coordinates("c1")));
    whitePieces->push_back(new Queen(PieceColor::WHITE, Coordinates("d1")));
    whitePieces->push_back(new King(PieceColor::WHITE, Coordinates("e1")));
    whitePieces->push_back(new Bishop(PieceColor::WHITE, Coordinates("f1")));
    whitePieces->push_back(new Knight(PieceColor::WHITE, Coordinates("g1")));
    whitePieces->push_back(new Rook(PieceColor::WHITE, Coordinates("h1")));

    blackPieces->push_back(new Rook(PieceColor::BLACK, Coordinates("a8")));
    blackPieces->push_back(new Knight(PieceColor::BLACK, Coordinates("b8")));
    blackPieces->push_back(new Bishop(PieceColor::BLACK, Coordinates("c8")));
    blackPieces->push_back(new Queen(PieceColor::BLACK, Coordinates("d8")));
    blackPieces->push_back(new King(PieceColor::BLACK, Coordinates("e8")));
    blackPieces->push_back(new Bishop(PieceColor::BLACK, Coordinates("f8")));
    blackPieces->push_back(new Knight(PieceColor::BLACK, Coordinates("g8")));
    blackPieces->push_back(new Rook(PieceColor::BLACK, Coordinates("h8")));

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

        if (this->selectedPiece != nullptr && this->isClientTurn) {
            this->handlePieceClickMove(event);
        }
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

                    if (this->selectedPiece != nullptr) {
                        switch (this->selectedPiece->getType()) {
                            case PieceType::PAWN: {
                                this->selectedPiece = dynamic_cast<Pawn*>(this->selectedPiece);
                                break;
                            }
                            case PieceType::ROOK: {
                                this->selectedPiece = dynamic_cast<Rook*>(this->selectedPiece);
                                break;
                            }
                            case PieceType::KNIGHT: {
                                this->selectedPiece = dynamic_cast<Knight*>(this->selectedPiece);
                                break;
                            }
                            case PieceType::BISHOP: {
                                this->selectedPiece = dynamic_cast<Bishop*>(this->selectedPiece);
                                break;
                            }
                            case PieceType::QUEEN: {
                                this->selectedPiece = dynamic_cast<Queen*>(this->selectedPiece);
                                break;
                            }
                            case PieceType::KING: {
                                this->selectedPiece = dynamic_cast<King*>(this->selectedPiece);
                                break;
                            }
                            default:
                                break;
                        }

                        this->selectedPiece->setPossibleMoves(this->playerPieces, this->enemyPieces);
                        this->selectedPiece->setPossibleAttacks(this->playerPieces, this->enemyPieces);
                    }
                }
            }
        }
    }
}

void Game::handlePieceClickMove(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            for (int row = 0; row < BOARD_SIZE; row++) {
                for (int col = 0; col < BOARD_SIZE; col++) {
                    if (this->board.getCell(row, col).isHovered(this->mousePos)) {
                        for (std::vector<Coordinates*>::size_type i = 0; i < this->selectedPiece->getPossibleMoves().size(); i++) {
                            if (this->selectedPiece->getPossibleMoves()[i]->getCoords() == this->board.getCell(row, col).getCoordinates().getCoords()) {
                                Coordinates oldCoord = this->selectedPiece->getCoordinates();
                                this->selectedPiece->setCoordinates(*this->selectedPiece->getPossibleMoves()[i]);
                                this->selectedPiece->setSelected(false);

                                std::string line =  this->selectedPiece->getName() + " " + ":" + oldCoord.getCoords() + "->" + this->selectedPiece->getCoordinates().getCoords();
                                sf::Packet packet;
                                packet << line;
                                this->client.sendPacket(packet);

                                this->logs.addLog(line);

                                if (this->selectedPiece->getType() == PieceType::PAWN) {
                                    Pawn *pawn = dynamic_cast<Pawn*>(this->selectedPiece);
                                    pawn->setFirstMove(false);
                                }

                                this->selectedPiece = nullptr;
                                this->isClientTurn = false;
                                return;
                            }
                        }

                        for (std::vector<Coordinates*>::size_type i = 0; i < this->selectedPiece->getPossibleAttacks().size(); i++) {
                            if (this->selectedPiece->getPossibleAttacks()[i]->getCoords() == this->board.getCell(row, col).getCoordinates().getCoords()) {
                                Coordinates oldCoord = this->selectedPiece->getCoordinates();
                                this->selectedPiece->setCoordinates(*this->selectedPiece->getPossibleAttacks()[i]);
                                this->selectedPiece->setSelected(false);

                                std::string line =  this->selectedPiece->getName() + "x" + ":" + oldCoord.getCoords() + "->" + this->selectedPiece->getCoordinates().getCoords();
                                sf::Packet packet;
                                packet << line;
                                this->client.sendPacket(packet);

                                this->logs.addLog(line);

                                for (std::vector<Piece*>::iterator it = this->enemyPieces->begin(); it != this->enemyPieces->end(); it++) {
                                    if ((*it)->getCoordinates().getCoords() == this->selectedPiece->getCoordinates().getCoords()) {
                                        this->enemyPieces->erase(it);
                                        break;
                                    }
                                }

                                if (this->selectedPiece->getType() == PieceType::PAWN) {
                                    Pawn *pawn = dynamic_cast<Pawn*>(this->selectedPiece);
                                    pawn->setFirstMove(false);
                                }

                                this->selectedPiece = nullptr;
                                this->isClientTurn = false;
                                return;
                            }
                        }
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

        std::string coords = this->enemyMoves.back();
        this->logs.addLog(coords);
        for (std::vector<Piece*>::iterator piece = this->enemyPieces->begin(); piece != this->enemyPieces->end(); piece++) {
            if ((*piece)->getName() == coords.substr(0, 1)) {
                if ((*piece)->getCoordinates().getCoords() == coords.substr(3, 2)) {
                    (*piece)->setCoordinates(Coordinates(coords.substr(7, 2)));

                    if (coords.substr(1, 1) == std::string(1, 'x')) {
                        for (std::vector<Piece*>::iterator it = this->playerPieces->begin(); it != this->playerPieces->end(); it++) {
                            if ((*it)->getCoordinates().getCoords() == coords.substr(7, 2)) {
                                this->playerPieces->erase(it);
                                break;
                            }
                        }
                    
                    }

                    break;
                }
            }
        }
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