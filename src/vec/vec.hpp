#pragma once

#include <cstring>

template <typename T, size_t InlineCap>
class SmallVector {
 private:
  char initial[sizeof(T) * InlineCap] = {0};
  size_t size = 0;
  size_t capacity = InlineCap;

 public:
  SmallVector(){};

  void push(T elem) {
    if (size < capacity) {
      std::memcpy(&initial[sizeof(T) * size], &elem, sizeof(T));
      size += 1;
    }
  }

  T& operator[](size_t index) { return (T&)(initial[sizeof(T) * index]); }

  const T* initial_begin() const {
    return reinterpret_cast<const T*>(&initial[0]);
  }
};