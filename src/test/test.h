#ifndef TEST_H
#define TEST_H

#include <iostream>

#define TEST_VERSION_MAJOR 2

class Test
{
    private:
        int m_value;
    public:
        Test(int value);
        void display();
};

#endif // TEST_H