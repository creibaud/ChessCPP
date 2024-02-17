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
        std::vector<sf::TcpSocket*> clients;

        sf::IpAddress address;
        unsigned short port;

        void connectClients(std::vector<sf::TcpSocket*> *clients);
        void disconnectClients(sf::TcpSocket *socket, std::vector<sf::TcpSocket*>::size_type index);

        void broadcastPacket(sf::Packet &packet, sf::TcpSocket *sender);
        void receivePacket(sf::TcpSocket *client, std::vector<sf::TcpSocket*>::size_type index);
        void managePackets();
    public:
        Server(const std::string &addr, unsigned short port);

        void run();
};

#endif // SERVER_H