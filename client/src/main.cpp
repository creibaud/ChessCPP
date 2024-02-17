#include "client/client.h"

int main() {
    Client client("localhost", 3000);
    client.connect();
    client.disconnect();
    return 0;
}