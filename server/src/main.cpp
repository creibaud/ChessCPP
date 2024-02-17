#include "server/server.h"

int main()
{
    std::string userInputAddr;
    unsigned int userInputPort;

    std::cout << "Enter the server address: ";
    std::cin >> userInputAddr;
    std::cout << "Enter the server port: ";
    std::cin >> userInputPort;

    Server server(userInputAddr, userInputPort);
    server.run();
    return 0;
}