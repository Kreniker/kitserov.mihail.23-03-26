#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <stdexcept>
namespace topit 
{
    template < class T >
    struct Vector
    {
      Vector();
      Vector(size_t size, const T& val);
      ~Vector();
      
      Vector(const Vector<T>& rhs);
      Vector<T>& operator=(const Vector<T>& rhs);
      Vector(Vector<T>&&) noexcept;
      Vector<T>& operator=(Vector<T>&&) noexcept;
      
      bool isEmpty() const noexcept;
      size_t getSize() const noexcept;
      size_t getCapacity() const noexcept;

      void pushBack(const T& val);
      void pushFront(const T& val);

      T& operator[](size_t id) noexcept;
      const T& operator[](size_t id) const noexcept;
      T& at(size_t id);
      const T& at(size_t id) const;

	  void swap(Vector<T>& rhs) noexcept;

	  ///////////////////////
	  //КЗ (copy, swap)
	  // Протестировать
	  void insert(size_t pos, const T& val);
	  void insert(size_t pos, const Vector<T> rhs, size_t beg, size_t e);
	  void erase(size_t pos);
	  //////////////////
	  // ДЗ
	  // 1. Реализовать итераторы. Тестировать не нужно
	  // 2. Придумать по 3 штуки insert/erase с итераторами. (нужны ещё константные итераторы, значит в Сумме 6)
	  struct VectorIterator;
	  void insert(VectorIterator pos, const T& val);
	  void erase(VectorIterator pos);
/////////////////////////////////////////////
	  template< class IT >
	  void insert(VectorIterator pos, IT begin, IT end);
    private:
      T* data_;
      size_t size_, capacity_;
      explicit Vector(size_t size);
    };
    template<class T>
    bool operator==(const Vector<T>& v1, const Vector<T>& v2);
    template<class T>
    bool operator!=(const Vector<T>& v1, const Vector<T>& v2);
}
template < class T >
topit::Vector<T>::Vector(): data_(nullptr), size_(0), capacity_(0)
{}
template < class T >
topit::Vector<T>::~Vector()
{
  delete [] data_;
}
template< class T >
bool topit::Vector<T>::isEmpty() const noexcept
{
  return !size_;
}
template<class T>
size_t topit::Vector<T>::getSize() const noexcept
{
  return size_;
}
template<class T>
topit::Vector<T>::Vector(const Vector<T>& rhs): Vector(rhs.getSize())
{
	for(size_t i = 0; i < getSize(); ++i) {
		data_[i] = rhs.data_[i];
	}
}
template<class T>
topit::Vector<T>::Vector(size_t size):
 data_(size ? new T[size] : nullptr),
 size_(size),
 capacity_(size)
{}
template<class T>
T& topit::Vector<T>::at(size_t id)
{
  return const_cast< T& >(static_cast< const Vector< T >* >(this) -> at(id));
}
template<class T>
const T& topit::Vector<T>::at(size_t id) const
{
    if (id < getSize()) {
        return data_[id];
    }
  throw std::out_of_range("bad id");
}
template<class T>
topit::Vector<T>::Vector(size_t size, const T& val):
 Vector(size)
{
  for (size_t i = 0; i < size; i++) {
    data_[i] = val;
  }
} 
template<class T>
size_t topit::Vector<T>::getCapacity() const noexcept
{
  return capacity_;
}
template<class T>
void topit::Vector<T>::pushBack(const T& val)
{
  if (size_ >= capacity_) {
    size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
	T* newData = new T[newCap];
    for (size_t i = 0; i < size_; ++i) {
      newData[i] = data_[i];
    }
    delete[] data_;
    data_ = newData;
    capacity_ = newCap;
  }
  data_[size_++] = val;
}
template<class T>
void topit::Vector<T>::pushFront(const T& val)
{
  Vector< T > cpy(*this);

  Vector<T> res(getSize() + 1);
  res[0] = val;
  for (size_t i = 0; i < getSize(); i++) {
  	res[i + 1] = (*this)[i];
  }
  swap(res);
}
template<class T>
T& topit::Vector<T>::operator[](size_t id) noexcept
{
  return data_[id];
}
template<class T>
const T& topit::Vector<T>::operator[](size_t id) const noexcept
{
  return data_[id];
}

template<class T>
bool topit::operator==(const Vector<T>& v1, const Vector<T>& v2) {
    if (v1.getSize() != v2.getSize())
        return false;
    for (size_t i = 0; i < v1.getSize(); ++i) {
        if (v1[i] != v2[i])
            return false;
    }
    return true;
}

template<class T>
bool topit::operator!=(const Vector<T>& v1, const Vector<T>& v2) {
    return !(v1 == v2);
}
template< class T >
topit::Vector< T >& topit::Vector<T>::operator=(const Vector<T>& rhs)
{
	Vector< T > cpy(rhs);
	swap(cpy);
	return *this;
}
template< class T >
void topit::Vector<T>::swap(Vector<T>& rhs) noexcept
{
	std::swap(data_, rhs.data_);
	std::swap(size_, rhs.size_);
	std::swap(capacity_, rhs.capacity_);
}
template<class T>
topit::Vector<T>::Vector(Vector<T>&& rhs) noexcept:
 data_(rhs.data_),
 size_(rhs.size_),
 capacity_(rhs.capacity_)
{
	rhs.data_ = nullptr;
}
template<class T>
topit::Vector<T>& topit::Vector<T>::operator=(Vector<T>&& rhs) noexcept
{
	Vector<T> cpy(std::move(rhs));
	swap(cpy);
	return *this;
}

template<class T>
void topit::Vector<T>::insert(size_t pos, const T& val)
{
	if (pos > size_) {
		throw std::out_of_range("Invalid pos for insert");
	}
	
    if (size_ < capacity_) {
    	try {
	        for (size_t i = size_; i > pos; --i) {
	            data_[i] = data_[i - 1];
	        }
	        data_[pos] = val;
	        ++size_;
	        return;
	    } catch(...) {
	    	throw;
	    }
    }
    size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
    T* new_data = new T[newCap];
	try {
		for (size_t i = 0; i < pos; i++) {
			new_data[i] = data_[i];
		}
		new_data[pos] = val;
		for (size_t i = pos; i < size_; i++) {
			new_data[i + 1] = data_[i];
		}
	} catch(...) {
		delete[] new_data;
		throw;
	}
	delete[] data_;
	data_ = new_data;
	size_ = size_ + 1;
	capacity_ = newCap;
}

template<class T>
void topit::Vector<T>::insert(size_t pos, const Vector<T> rhs, size_t beg, size_t e)
{
	if (pos > size_) {
        throw std::out_of_range("Vector::insert (range): pos out of range");
    }
    if (beg > e || e > rhs.size_) {
        throw std::out_of_range("Vector::insert (range): invalid range");
    }
    size_t count = e - beg;
    size_t newPos = pos;
    Vector<T> cpy(*this);
    try {
	    for (size_t i = 0; i < count; i++) {
	    	cpy.insert(newPos++, rhs.data_[beg + i]);
	    }
	} catch(...) {
		throw;
	}
	this->swap(cpy);
}

template<class T>
void topit::Vector<T>::erase(size_t pos)
{
	if (pos >= size_) {
		throw;
	}
	if (size_ == 1) {
		delete[] data_;
		size_ = 0;
		capacity_ = 0;
		return;
	}
	Vector<T> cpy(*this);
	try {
		for(size_t i = pos; i < size_ - 1; i++) {
			cpy.data_[i] = cpy.data_[i + 1];
		}
	} catch(...) {
		throw;
	}
	this->swap(cpy);
	size_ = size_ - 1;
}
#endif
