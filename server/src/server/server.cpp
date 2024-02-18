#include "server.h"

Server::Server(const std::string &addr, unsigned short port) : port(port) {
    this->address = sf::IpAddress(addr);
    if (this->listener.listen(this->port, this->address) != sf::Socket::Done) {
        std::cout << "[!] Server can't be started on " << this->address << ":" << this->port << std::endl;
    } else {
        std::cout << "[*] Server started on " << addr << ":" << port << std::endl;
    }
}

void Server::connectClients(std::map<std::string, sf::TcpSocket*> *clients) {
    while (true) {
        sf::TcpSocket *newClient = new sf::TcpSocket();
        if (this->listener.accept(*newClient) == sf::Socket::Done) {
            std::string pseudo;
            sf::Packet packet;
            if (newClient->receive(packet) == sf::Socket::Done) {
                packet >> pseudo;
                std::cout << "[+] New client connected : " << pseudo << " (" << newClient->getRemoteAddress() << ":" << newClient->getRemotePort() << ")" << std::endl;
                newClient->setBlocking(false);
                clients->insert(std::pair<std::string, sf::TcpSocket*>(pseudo, newClient));
            } else {
                std::cout << "[!] Server can't receive pseudo from " << newClient->getRemoteAddress() << ":" << newClient->getRemotePort() << std::endl;
                delete newClient;
                continue;
            }
        } else {
            std::cout << "[!] Server can't accept new client" << std::endl;
            delete newClient;
        }
    }
}

void Server::disconnectClients(sf::TcpSocket *socket, std::string pseudo) {
    std::cout << "[-] Client disconnected : " << pseudo << " (" << socket->getRemoteAddress() << ":" << socket->getRemotePort() << ")" << std::endl;
    socket->disconnect();
    delete socket;
    this->clients.erase(pseudo);
}

void Server::broadcastPacket(sf::Packet &packet, sf::TcpSocket *sender) {
    for (std::map<std::string, sf::TcpSocket*>::iterator it = this->clients.begin(); it != this->clients.end(); it++) {
        sf::TcpSocket *client = it->second;
        if (client->getRemoteAddress() != sender->getRemoteAddress() || client->getRemotePort() != sender->getRemotePort()) {
            if (client->send(packet) != sf::Socket::Done) {
                std::cout << "[!] Server can't send message to " << it->first << " (" << client->getRemoteAddress() << ":" << client->getRemotePort() << ")" << std::endl;
            }
        }
    }
}

void Server::receivePacket(sf::TcpSocket *client, std::string pseudo) {
    sf::Packet packet;
    if (client->receive(packet) == sf::Socket::Disconnected) {
        this->disconnectClients(client, pseudo);
    } else {
        if (packet.getDataSize() > 0) {
            std::string message;
            packet >> message;
            packet.clear();

            packet << message << pseudo;

            this->broadcastPacket(packet, client);
            std::cout << pseudo << " (" << client->getRemoteAddress() << ":" << client->getRemotePort() << ") : '" << message << "'" << std::endl;
        }
    }
}

void Server::managePackets() {
    while (true) {
        for (std::map<std::string, sf::TcpSocket*>::iterator it = this->clients.begin(); it != this->clients.end(); it++) {
            sf::TcpSocket *client = it->second;
            std::string pseudo = it->first;
            this->receivePacket(client, pseudo);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Server::run() {
    std::thread connectionThread(&Server::connectClients, this, &this->clients);
    this->managePackets();
}