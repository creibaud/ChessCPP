#ifndef SERVER_H
#define SERVER_H

#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

class Server {
    private:
        sf::TcpListener listener;
        std::map<std::string, sf::TcpSocket*> clients;

        sf::IpAddress address;
        unsigned short port;

        void connectClients(std::map<std::string, sf::TcpSocket*> *clients);
        void disconnectClients(sf::TcpSocket *socket, std::string pseudo);

        void broadcastPacket(sf::Packet &packet, sf::TcpSocket *sender);
        void receivePacket(sf::TcpSocket *client, std::string pseudo);
        void managePackets();
    public:
        Server(const std::string &addr, unsigned short port);

        void run();
};

#endif // SERVER_H