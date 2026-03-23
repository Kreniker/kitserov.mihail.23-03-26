#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
namespace identifier {
    template < class T >
    struct Vector
    {
      T* data;
      size_t size, capacity;
    };
}

#endif