#include <ios>
#include <iostream> 
#include "vector.hpp"
#include <cstddef>
#include <stdexcept>
#include <utility>

using topit::Vector;
bool test1()
{
    Vector< int > v;
    return v.isEmpty();
}
bool test2()
{
    Vector<int> v;
    return v.getSize() == 0;
}
bool test3()
{
    constexpr size_t size = 3ull;
    Vector<int> v(size);
    return v.getSize() == size;
}
bool test4()
{
    constexpr size_t size = 3ull;
    Vector<int> v(size);
    try {
        v.at(0);
        return true;
    } catch(...) {
        return false;
    }
}
bool test5()
{
    constexpr size_t size = 3ull;
    Vector<int> v(size);
    try {
        v.at(size + 1);
        return false;
    } catch(const std::out_of_range&) {
        return true;
    } catch(...) {
        return false;
    }
}

int main()
{
    using test_t = bool(*)();
    using case_t = std::pair<test_t, const char*>;
    case_t tests[] = {
        {test1, "Default constructor vector must be empty"},
        {test2, "Default vector must has zero size"},
        {test3, "Vector constructor with size has non-zero size"},
        {test4, "In range access does not generate exceptions"},
        {test5, "Out of range access generates std::out_of_ranges exceptions"}
    };
    size_t count = sizeof(tests) / sizeof(case_t);
    std::cout << std::boolalpha;
    for(size_t i = 0; i < count; ++i) {
        std::cout << tests[i].first() << ": " << tests[i].second << "\n";
    }
    return 0;
}