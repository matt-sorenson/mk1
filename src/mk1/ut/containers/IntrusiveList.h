#pragma once

namespace mk1::ut::containers {

template <typename T>
class IntrusiveList {
  public:
    class Node {
      public:
        const T* get_next() const { return _next; }
        T* get_next() { return _next; }
        void set_next(T* next) { _next = next; }
      private:
        T* _next = nullptr;
    };

    void push_front(T* ptr);
    void push_back(T* ptr);

    void erase(T* ptr);

    T* front() { return _head; }
    const T* front() const { return _head; }
    size_t size() const;

  private:
    T* _head = nullptr;
};
}

#include <mk1/ut/containers/IntrusiveList.cpp.inl>
