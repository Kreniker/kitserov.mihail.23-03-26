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
bool test8() {
	Vector< int > v(2, 0);
	Vector< int > ya = v;
	return ya == v;
}
bool test9() {
	Vector< int > v;
	Vector<int> ya(2, 0);
	bool res = v != ya;
	v = ya;
	return res && v == ya;
}
bool test10() {
	Vector<int> v(2, 0);
	Vector<int> yav(3, 1);

	Vector<int> cpy_v(v);
	Vector<int> cpy_yav(yav);

	v.swap(yav);

	return cpy_v == yav && cpy_yav == v;
}
bool test11() {
	Vector<int> v(2,0);
	Vector<int> cpy_v(v);
	Vector<int> yav = std::move(v);
	return yav == cpy_v;
}
bool test12() {
	Vector<int> v(2,0);
	Vector<int> cpy_v(v);
	Vector<int> yav;

	yav = std::move(v);
	return yav == cpy_v;
}
bool test13() {
	Vector< int > v(2, 0);
	v.insert(1, 1);
	return v[0] == 0 && v[1] == 1 && v[2] == 0;
}
bool test14() {
	Vector< int > v(2, 0);
	try {
		v.insert(3, 1);
		return false;
	} catch(...) {
		return true;
	}
}
bool test15() {
	Vector< int > v(2, 0);
	Vector< int > yav(4, 2);
	v.insert(1, yav, 1, 3);
	return v[0] == 0 && v[1] == 2 && v[2] == 2 && v[3] == 0;
}
bool test16() {
	Vector< int > v(2, 0);
	Vector< int > yav(4, 2);
	try {
		v.insert(5, yav, 1, 3);
		return false;
	} catch(...) {
		return true;
	}
}
bool test17() {
	Vector< int > v(2, 0);
	Vector< int > yav(4, 2);
	try {
		v.insert(1, yav, 1, 6);
		return false;
	} catch(...) {
		return true;
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
        {test7, "Out of range access for const Vector generates std::out_of_ranges exceptions"},
        {test8, "Copy constant"},
        {test9, "copy assignment operator"},
        {test10, "Swap for two vectors"},
        {test11, "Move construstor"},
        {test12, "move assignment operator"},
        {test13, "Insert one element"},
        {test14, "Insert out of range generate exception"},
        {test15, "Insert part of another vector"},
        {test16, "insert another vector generate out of range because bad insert-pos"},
        {test17, "insert another vector generate out of range because bad insert-range"}
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
