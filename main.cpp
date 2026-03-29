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
    Vector<int> v(size, 0);
    return v.getSize() == size && v.getCapacity() == size;
}
bool test4()
{
    constexpr size_t size = 3ull;
    Vector<int> v(size, 1);
    try {
        int& value = v.at(0);
        int& value1 = v[0];
        return value == 1 and value1 == 1;
    } catch(...) {
        return false;
    }
}
bool test5()
{
    constexpr size_t size = 3ull;
    Vector<int> v(size, 0);
    try {
        v.at(size + 1);
        return false;
    } catch(const std::out_of_range&) {
        return true;
    } catch(...) {
        return false;
    }
}
bool test6()
{
    constexpr size_t size = 3ull;
    const Vector<int> v(size, 1);
    try {
        const int& value = v.at(0);
        const int& value1 = v[0];
        return value == 1 and value1 == 1;
    } catch(...) {
        return false;
    }
}
bool test7()
{
    constexpr size_t size = 3ull;
    const Vector<int> v(size, 0);
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
        {test3, "Vector constructor with size has non-zero size and capacity"},
        {test4, "In range access does not generate exceptions"},
        {test5, "Out of range access generates std::out_of_ranges exceptions"},
        {test6, "In range access for const Vector does not generate exceptions"},
        {test7, "Out of range access for const Vector generates std::out_of_ranges exceptions"}
    };
    size_t count = sizeof(tests) / sizeof(case_t);
    std::cout << std::boolalpha;
    bool result = true;
    size_t successes = 0, fails = 0;
    for(size_t i = 0; i < count; ++i) {
        bool case_result = tests[i].first();
        successes += case_result;
        fails += !case_result;
        result = result && case_result;
        std::cout << case_result << ": " << tests[i].second << "\n";
    }
    std::cout << "SUMMARY\n";
    std::cout << result << ": TEST_RESULT\n";
    std::cout << fails << ": failed_tests\n";
    std::cout << successes << ": successes_tests\n";
    return 0;
}
