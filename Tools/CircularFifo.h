// In the name of Allah

#ifndef __COMTOS_CIRC_BUF_FLAG_H
#define __COMTOS_CIRC_BUF_FLAG_H

#include <cstddef>

namespace comtos
{
    namespace tools
    {
        template <typename dtype>
        class CircularFifo
        {
        public:
            explicit CircularFifo() = delete;
            explicit CircularFifo(CircularFifo &) = delete;
            explicit CircularFifo(dtype * buf, size_t buf_size);

            bool available();
            bool isFull();
            dtype read();
            void write(dtype d);
            void clear();
            void replaceLastValue(dtype d);
            dtype * get_buf();
            void defragment();

        private:
            dtype * const _buf;
            const size_t _buf_size;
            size_t _cur_read;
            size_t _cur_write;
            size_t _iter_cur(size_t cur);
            size_t _back_cur(size_t cur);
        };
    };
}

#endif