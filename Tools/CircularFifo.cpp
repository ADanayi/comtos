// In the name of Allah

#include "CircularFifo.h"

/*
template <class dtype>
        CircularFifo<dtype>::
*/

namespace comtos
{
    namespace tools
    {
        template <class dtype>
        CircularFifo<dtype>::CircularFifo(dtype *buf, size_t buf_size)
            : _buf(buf),
              _buf_size(buf_size)
        {
            _cur_read = 0;
            _cur_write = 0;
        };

        template <class dtype>
        bool CircularFifo<dtype>::available()
        {
            return _cur_read != _cur_write;
        };

        template <class dtype>
        size_t CircularFifo<dtype>::_iter_cur(size_t cur)
        {
            cur++;
            return cur % _buf_size;
        };

        template <class dtype>
        size_t CircularFifo<dtype>::_back_cur(size_t cur)
        {
            if (cur == 0)
                return _buf_size - 1;
            return cur - 1;
        };

        template <class dtype>
        bool CircularFifo<dtype>::isFull()
        {
            return _iter_cur(_cur_write) == _cur_read;
        };

        template <class dtype>
        dtype CircularFifo<dtype>::read()
        {
            while (!available())
            {
            };
            dtype d = _buf[_cur_read];
            _cur_read = _iter_cur(_cur_read);
            return d;
        };

        template <class dtype>
        void CircularFifo<dtype>::write(dtype d)
        {
            while (isFull())
            {
            };
            _buf[_cur_write] = d;
            _cur_write = _iter_cur(_cur_write);
        };

        template <class dtype>
        void CircularFifo<dtype>::clear()
        {
            _cur_write = 0;
            _cur_read = 0;
        }

        template <class dtype>
        void CircularFifo<dtype>::replaceLastValue(dtype d)
        {
            _buf[_back_cur(_cur_write)] = d;
        }

        template <class dtype>
        dtype *CircularFifo<dtype>::get_buf()
        {
            return _buf;
        }

        template <class dtype>
        void CircularFifo<dtype>::defragment()
        {
            if (!available())
            {
                _cur_read = 0;
                _cur_write = 0;
                return;
            }
            while (_cur_read != 0)
            {
                size_t c = _cur_read;
                for (size_t i = 0; i < _buf_size; i++)
                {
                    
                }
            }
        }
    }
} // namespace comtos
