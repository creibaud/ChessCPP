#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <iostream>
#include <string>

class Client {
    private:
        sf::IpAddress address;
        unsigned short port;
        
        sf::TcpSocket socket;

        std::string pseudo;

    public:
        Client(const std::string& address, unsigned short port);

        void sendPseudo();
        void connect();
        void disconnect();
};

#endif // CLIENT_H