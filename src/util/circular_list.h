// ---------------------------------------------
//           This file is part of
//      _  _   __    _   _    __    __
//     ( \/ ) /__\  ( )_( )  /__\  (  )
//      \  / /(__)\  ) _ (  /(__)\  )(__
//      (__)(__)(__)(_) (_)(__)(__)(____)
//
//     Yet Another HW Abstraction Library
//      Copyright (C) Andreas Terstegge
//      BSD Licensed (see file LICENSE)
//
// ---------------------------------------------
//
//  This is a simple generic implementation of
//  a circular double-linked list. The type T
//  is expected to have the following attributes:
//
//  T *  _prev;      pointer to the previous element
//  T *  _next;      pointer to the next element
//  bool _linked_in; flag to signal if the instance
//                   is member of the list
//
//  This class only holds pointers to the elements,
//  and does not do any kind of memory management.
//  It only 'organizes' existing elements.
//  If there are access problems to the attributes
//  above, a C++ friendship to this class might be
//  declared.
//  Main usage of this class in YAHAL is the multitasking
//  kernel, which organizes task_base instances as a
//  circular list. It is also used for the condition_variable.

#ifndef _CIRCULAR_LIST_H_
#define _CIRCULAR_LIST_H_

template<typename T>
class circular_list {
public:

    circular_list() {
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
    }

    void push_back(T * elem) {
        if (_tail) {
            // There are entries already
            elem->_next = _head;
            elem->_prev = _tail;
            _head->_prev = elem;
            _tail->_next = elem;
            _tail = elem;
        } else {
            // We are the first element
            elem->_next = elem;
            elem->_prev = elem;
            _head=_tail = elem;
        }
        elem->_linked_in = true;
        ++_size;
    }

    void remove(T * elem) {
        if (_size == 1) {
            // We are the last element
            _head = nullptr;
            _tail = nullptr;
        } else {
            // There is more than one element left
            elem->_prev->_next = elem->_next;
            elem->_next->_prev = elem->_prev;
            if (_head == elem) _head = elem->_next;
            if (_tail == elem) _tail = elem->_prev;
        }
        elem->_linked_in = false;
        --_size;
    }

    inline T * getHead() const { return _head; }
    inline T * getTail() const { return _tail; }
    inline int getSize() const { return _size; }

private:

    T *  _head;
    T *  _tail;
    int  _size;
};

#endif /* _CIRCULAR_LIST_H_ */
