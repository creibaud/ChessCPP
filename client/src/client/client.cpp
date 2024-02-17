#include "client.h"

Client::Client(const std::string& address, unsigned short port) : port(port){
    this->address = sf::IpAddress(address);
}

void Client::sendPseudo() {
    std::cout << "Enter a pseudo: ";
    std::cin >> this->pseudo;
    
    sf::Packet packet;
    packet << this->pseudo;
    if (this->socket.send(packet) != sf::Socket::Done) {
        std::cerr << "[!] Failed to send pseudo" << std::endl;
    }
}

void Client::connect() {
    if (this->socket.connect(this->address, this->port) != sf::Socket::Done) {
        std::cerr << "[!] Failed to connect to server" << std::endl;
        return;
    } else {
        this->sendPseudo();
        std::cout << "[+] Connected to server : " << this->address << std::endl;
    }
}

void Client::disconnect() {
    std::cout << "[!] Disconnected from server :" << this->address << std::endl;
    this->socket.disconnect();
}