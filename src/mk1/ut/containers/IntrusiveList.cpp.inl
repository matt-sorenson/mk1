#pragma once

namespace mk1::ut::containers {

template <typename T>
void IntrusiveList<T>::push_front(T* ptr)
{
    ptr->set_next(_head);
    _head = ptr;
}

template <typename T>
void IntrusiveList<T>::push_back(T* ptr)
{
    if (!_head) {
        _head = ptr;
    } else {
        T* curr = _head;
        while (curr->get_next()) {
            curr = curr->get_next();
        }

        curr->set_next(ptr);
    }
}

template <typename T>
void IntrusiveList<T>::erase(T* ptr)
{
    assert_throw(nullptr != _head,
                 "Trying to erase element from empty IntrusiveList.");

    if (_head == ptr) {
        _head = ptr->get_next();
        return;
    }

    for (T* curr = _head; curr; curr = curr->get_next()) {
        if (curr->get_next() == ptr) {
            curr->set_next(ptr->get_next());
            return;
        }
    }

    throw std::runtime_error("Element doesn't exist in IntrusiveList.");
}

template <typename T>
size_t IntrusiveList<T>::size() const
{
    size_t count = 0;
    T* curr = _head;

    while (curr) {
        count += 1;
        curr = curr->get_next();
    }

    return count;
}
}
