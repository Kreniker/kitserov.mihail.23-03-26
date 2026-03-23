#include <iostream> 
#include "vector.hpp"
#include <cstddef>

bool test1()
{
    using topit::Vector;
    Vector< int > v;
    return v.isEmpty();
}

int main()
{
    using test_t = bool(*)();
    test_t tests[] = {
        test1
    };
    size_t count = sizeof(tests) / sizeof(tests[0]);
    for(size_t i = 0; i < count; ++i) {
        std::cout << tests[i]() << ": " << i << "\n";
    }
}