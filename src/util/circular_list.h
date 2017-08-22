/*
 * circular_list.h
 *
 *  Created on: 27.07.2017
 *      Author: andreas
 */

#ifndef CIRCULAR_LIST_H_
#define CIRCULAR_LIST_H_

template<typename T>
class circular_list {

    public:

        circular_list() {
            _linked_in = false;
            _next      = nullptr;
            _prev      = nullptr;
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
            _linked_in = true;
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
            _linked_in = false;
            --_size;
        }

        inline bool linkedIn() const { return _linked_in; }
        inline T *  getNext()  const { return _next; }
        inline T *  getPrev()  const { return _prev; }
        inline T *  getHead()  const { return _head; }
        inline T *  getTail()  const { return _tail; }
        inline int  getSize()  const { return _size; }

    protected:

        bool        _linked_in;
        T *         _next;
        T *         _prev;
        static T *  _head;
        static T *  _tail;
        static int  _size;
};

template<typename T>
T * circular_list<T>::_head = nullptr;

template<typename T>
T * circular_list<T>::_tail = nullptr;

template<typename T>
int circular_list<T>::_size = 0;

#endif /* CIRCULAR_LIST_H_ */
