#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
namespace topit {
    template < class T >
    struct Vector
    {
      T* data;
      size_t size, capacity;
    };
    template<class T>
    bool operator==(Vector<T> v1, Vector<T> v2)
    {
        return v1.data == v2.data;
    }
}

#endif