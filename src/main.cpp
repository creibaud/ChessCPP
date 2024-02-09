#include <iostream>
#include "test/test.h"

int main() {
    Test test(5);
    test.display();
    std::cout << "Version: " << TEST_VERSION_MAJOR << std::endl;
    return 0;
}