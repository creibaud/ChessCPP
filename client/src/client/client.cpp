#include "client.h"

Client::Client() {
    this->color = "";

    std::cout << "[*] Client started" << std::endl;
    std::cout << "[*] Enter your pseudo : ";
    std::cin >> this->pseudo;
}

std::string Client::getPseudo() const {
    return this->pseudo;
}

std::string Client::getColor() const {
    return this->color;
}

std::vector<std::string> Client::getEnemyMoves() const {
    return this->enemyMoves;
}

void Client::connect(const std::string &addr, unsigned short port) {
    if (this->socket.connect(addr, port) != sf::Socket::Done) {
        std::cout << "[!] Can't connect to " << addr << ":" << port << std::endl;
    } else {
        sf::Packet packet;
        packet << this->pseudo;
        this->sendPacket(packet);

        std::cout << "[*] Connected to " << addr << ":" << port << std::endl;
        this->isConnected = true;

        if (this->socket.receive(this->lastPacket) == sf::Socket::Done) {
            this->lastPacket >> this->color;
            std::cout << "[*] You are " << this->color << std::endl;
        } else {
            std::cout << "[!] Can't get color from server" << std::endl;
        }

        this->lastPacket.clear();
    }
}

void Client::receivePacket(sf::TcpSocket *socket) {
    while (true) {
        if (socket->receive(this->lastPacket) == sf::Socket::Done) {
            std::string message;
            this->lastPacket >> message;
            this->enemyMoves.push_back(message);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Client::sendPacket(sf::Packet &packet) {
    if (packet.getDataSize() > 0 && this->socket.send(packet) != sf::Socket::Done) {
        std::cout << "[!] Can't send packet" << std::endl;
    }
}

void Client::run() {
    std::thread receiveThread(&Client::receivePacket, this, &this->socket);
    receiveThread.detach();
}