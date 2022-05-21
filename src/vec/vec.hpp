#pragma once

#include <cstring>
#include <stdexcept>

namespace vec {

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
};

}  // namespace vec