#include "client/client.h"

int main(){
    std::string userInputAddr;
     unsigned int userInputPort;

    std::cout << "Enter the server address: ";
    std::cin >> userInputAddr;
    std::cout << "Enter the server port: ";
    std::cin >> userInputPort;

    Client client;
    client.connect(userInputAddr, userInputPort);
    client.run();
    return 0;
}