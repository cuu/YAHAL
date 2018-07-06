
#ifndef _FIFO_H_
#define _FIFO_H_

#include "yahal_assert.h"

template<typename T>
class FIFO {
public:
    FIFO(int size)
    : _buffer_size(size), _buffer(new T[_buffer_size]),
      _need_wrap(_buffer + _buffer_size), _get_ptr(_buffer), _put_ptr(_buffer)
    {
        yahal_assert( _buffer != nullptr);
    }

    ~FIFO() {
        delete [] _buffer;
    }

    bool get(T & data) volatile {
        if (_get_ptr == _put_ptr) {
            return false;
        }
        T * nextget = _get_ptr + 1;
        if (nextget == _need_wrap) {
            nextget =  _buffer;
        }
        data = *_get_ptr;
        _get_ptr = nextget;
        return true;
    }

    bool put(const T & data) volatile {
        T * nextput =  _put_ptr + 1;
        if (nextput == _need_wrap){
            nextput =  _buffer;
        }
        if (nextput == _get_ptr) {
            return false;
        } else {
            *_put_ptr = data;
             _put_ptr = nextput;
        }
        return true;
    }

    int available_get() volatile {
        int res = _put_ptr - _get_ptr;
        if (res < 0) {
            res += _buffer_size;
        }
        return res;
    }

    volatile int available_put() volatile {
        return _buffer_size - available_get() -1;
    }

private:

    int _buffer_size;
    T * _buffer;
    T * _need_wrap;
    T * _get_ptr;
    T * _put_ptr;
};

#endif // _FIFO_H_ */
