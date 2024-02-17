#include "server.h"

Server::Server(const std::string &address, unsigned short port) : port(port) {
    this->address = sf::IpAddress(address);
}

void Server::run() {
    if (this->listener.listen(this->port, this->address) != sf::Socket::Done) {
        std::cerr << "[!] Failed to bind to port " << this->port << std::endl;
        return;
    }

    while (true) {
        handleClientConnect();
        handleClientDisconnect();
    }
}

void Server::handleClientConnect() {
    sf::TcpSocket *client = new sf::TcpSocket();
    if (listener.accept(*client) == sf::Socket::Done) {
        sf::Packet packet;
        if (client->receive(packet) == sf::Socket::Done) {
            std::string pseudo;
            packet >> pseudo;
            std::cout << "[+] Client connected: " << pseudo << " (" << client->getRemoteAddress() << ")" << std::endl;
            this->clients.insert(std::make_pair(pseudo, client));
        } else {
            delete client;
        }
    } else {
        delete client;
    }
}

void Server::handleClientDisconnect() {
    for (std::map<std::string, sf::TcpSocket*>::iterator it = this->clients.begin(); it != this->clients.end(); ++it) {
        sf::Packet packet;
        sf::TcpSocket *client = it->second;
        if (client->receive(packet) == sf::Socket::Disconnected) {
            std::cout << "[-] Client disconnected: " << it->first << " (" << it->second->getRemoteAddress() << ")" << std::endl;
            delete client;
            this->clients.erase(it);
            break;
        }
    }
}

Server::~Server() {
    for (std::map<std::string, sf::TcpSocket*>::iterator it = this->clients.begin(); it != this->clients.end(); ++it) {
        delete it->second;
    }
    this->clients.clear();
}