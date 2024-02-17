#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <map>
#include <vector>

class Server {
    private:
        sf::IpAddress address;
        unsigned short port;

        sf::TcpListener listener;
        std::map<std::string, sf::TcpSocket*> clients;

    public:
        Server(const std::string& address, unsigned short port);

        void run();
        void handleClientConnect();
        void handleClientDisconnect();

        ~Server();
};

#endif // SERVER_H