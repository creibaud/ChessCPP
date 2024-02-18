#include "client.h"

Client::Client() {
    std::cout << "[*] Client started" << std::endl;
    std::cout << "[*] Enter your pseudo : ";
    std::cin >> this->pseudo;
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
    }
}

void Client::receivePacket(sf::TcpSocket *socket) {
    while (true) {
        if (socket->receive(this->lastPacket) == sf::Socket::Done) {
            std::string message;
            std::string senderPseudo;
            this->lastPacket >> message >> senderPseudo;
            std::cout << "[" << senderPseudo << "] -> '" << message << "'" << std::endl;
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
    
    while (this->isConnected) {
        std::string userInput;
        std::getline(std::cin, userInput);

        if (userInput.size() < 1) {
            continue;
        }

        sf::Packet replyPacket;
        replyPacket << userInput;
        this->sendPacket(replyPacket);
    }
}