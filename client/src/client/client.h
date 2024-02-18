#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

class Client {
    private:
        sf::TcpSocket socket;
        sf::Packet lastPacket;

        std::string pseudo;
        std::string color;
        bool isConnected = false;
    public:
        Client();

        std::string getPseudo() const;
        std::string getColor() const;

        void connect(const std::string &addr, unsigned short port);

        void receivePacket(sf::TcpSocket *socket);
        void sendPacket(sf::Packet &packet);
        
        void run();
};
#endif // CLIENT_H