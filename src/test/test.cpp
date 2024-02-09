#include "test.h"

Test::Test(int value) : m_value(value) {}

void Test::display() {
    std::cout << "Value: " << this->m_value << std::endl;
}