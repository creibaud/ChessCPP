#include "server.h"

Server::Server(const std::string &addr, unsigned short port) : port(port) {
    this->address = sf::IpAddress(addr);
    if (this->listener.listen(this->port, this->address) != sf::Socket::Done) {
        std::cout << "[!] Server can't be started on " << this->address << ":" << this->port << std::endl;
    } else {
        std::cout << "[*] Server started on " << addr << ":" << port << std::endl;
    }
}

void Server::connectClients(std::vector<sf::TcpSocket*> *clients) {
    while (true) {
        sf::TcpSocket *newClient = new sf::TcpSocket();
        if (this->listener.accept(*newClient) == sf::Socket::Done) {
            newClient->setBlocking(false);
            clients->push_back(newClient);
            std::cout << "[+] New client connected " << newClient->getRemoteAddress() << ":" << newClient->getRemotePort() << std::endl;
        } else {
            std::cout << "[!] Server can't accept new client" << std::endl;
            delete newClient;
        }
    }
}

void Server::disconnectClients(sf::TcpSocket *socket, std::vector<sf::TcpSocket*>::size_type index) {
    std::cout << "[-] Client disconnected " << socket->getRemoteAddress() << ":" << socket->getRemotePort() << std::endl;
    socket->disconnect();
    delete socket;
    this->clients.erase(this->clients.begin() + index);
}

void Server::broadcastPacket(sf::Packet &packet, sf::TcpSocket *sender) {
    for (std::vector<sf::TcpSocket*>::iterator client = this->clients.begin(); client != this->clients.end(); client++) {
        if ((*client)->getRemoteAddress() != sender->getRemoteAddress() || (*client)->getRemotePort() != sender->getRemotePort()) {
            if ((*client)->send(packet) != sf::Socket::Done) {
                std::cout << "[!] Server can't send message to " << (*client)->getRemoteAddress() << ":" << (*client)->getRemotePort() << std::endl;
            }
        }
    }
}

void Server::receivePacket(sf::TcpSocket *client, std::vector<sf::TcpSocket*>::size_type index) {
    sf::Packet packet;
    if (client->receive(packet) == sf::Socket::Disconnected) {
        this->disconnectClients(client, index);
    } else {
        if (packet.getDataSize() > 0) {
            std::string message;
            packet >> message;
            packet.clear();

            packet << message << client->getRemoteAddress().toString() << client->getRemotePort();

            this->broadcastPacket(packet, client);
            std::cout << client->getRemoteAddress().toString() << ":" << client->getRemotePort() << " -> '" << message << "'" << std::endl;
        }
    }
}

void Server::managePackets() {
    while (true) {
        for (std::vector<sf::TcpSocket*>::size_type i = 0; i < this->clients.size(); i++) {
            this->receivePacket(this->clients[i], i);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Server::run() {
    std::thread connectionThread(&Server::connectClients, this, &this->clients);
    this->managePackets();
}