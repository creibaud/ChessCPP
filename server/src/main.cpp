#include "server/server.h"

int main() {
    Server server("localhost", 3000);
    server.run();
    return 0;
}