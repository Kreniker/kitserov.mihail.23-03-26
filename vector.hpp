#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
namespace topit {
    template < class T >
    struct Vector
    {
      Vector();
      ~Vector();
      bool isEmpty() const noexcept;
    private:
      T* data;
      size_t size, capacity;
    };
    template<class T>
    bool operator==(const Vector<T>& v1, const Vector<T>& v2)
    {
        return v1.data == v2.data;
    }
}

#endif