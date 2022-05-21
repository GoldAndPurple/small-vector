#pragma once

#include <cstring>
#include <stdexcept>

namespace vec {

/* template <typename T, size_t inline_cap>
class Veciterator; */

template <typename T, size_t inline_cap>
class SmallVector {
 private:
  char initial[sizeof(T) * inline_cap] = {0};
  size_t size = 0;
  size_t capacity = inline_cap;
  size_t heap_cap = 0;
  T* data = nullptr;

 public:
  SmallVector(){};
  ~SmallVector() { delete[] data; };

  size_t Size() const { return size; }
  size_t Capacity() const { return capacity; }
  size_t InlineCapacity() const { return inline_cap; }

  void Push(T elem) {
    if (size < inline_cap) {
      std::memcpy(&initial[sizeof(T) * size], &elem, sizeof(T));
    } else {
      if (data == nullptr) {
        capacity *= 2;
        data = new T[capacity];
      } else if (size == capacity) {
        capacity *= 2;
        T* old = data;
        data = new T[capacity];
        std::memcpy(data, old, sizeof(T) * size);
        delete[] old;
      }
      data[size - inline_cap] = elem;
    }
    size += 1;
  }

  void Pop() {
    if (size == 0) {
      return;
    }
    size -= 1;
  }

  const T& operator[](size_t index) const {
    if (index < inline_cap) {
      return (T&)(initial[sizeof(T) * index]);
    } else if (index < size) {
      return data[size - inline_cap - 1];
    } else {
      throw std::out_of_range("Small vector out of bounds");
    }
  }

  struct iterator {
   public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;

    iterator(const pointer ptr, pointer l, pointer f)
        : m_ptr(ptr), last_on_stack(l), first_in_heap(f) {}
    iterator(const iterator& other)
        : m_ptr(other.m_ptr),
          last_on_stack(other.last_on_stack),
          first_in_heap(other.first_in_heap) {}

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }

    iterator& operator++() {
      if (m_ptr == last_on_stack) {
        m_ptr = first_in_heap;
      } else {
        m_ptr++;
      }
      return *this;
    }

    friend bool operator==(const iterator& a, const iterator& b) {
      return a.m_ptr == b.m_ptr;
    };
    friend bool operator!=(const iterator& a, const iterator& b) {
      return a.m_ptr != b.m_ptr;
    };

   private:
    pointer m_ptr;
    pointer last_on_stack;
    pointer first_in_heap;
  };

  iterator begin() {
    return iterator(
        reinterpret_cast<const T*>(&initial[0]),
        &initial[inline_cap - 1],
        data);
  }
  iterator end() {
    return iterator(
        reinterpret_cast<const T*>(&data[size - 1] + sizeof(T)),
        &initial[inline_cap - 1],
        data);
  }
};

}  // namespace vec