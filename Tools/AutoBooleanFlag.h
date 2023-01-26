// In the name of Allah

#ifndef __COMTOS_AUTO_BOOLEAN_FLAG_H
#define __COMTOS_AUTO_BOOLEAN_FLAG_H

namespace comtos
{
    namespace tools
    {
        class AutoBooleanFlag
        {
        public:
            explicit AutoBooleanFlag();
            explicit AutoBooleanFlag(AutoBooleanFlag &) = delete;

            void set(bool value = true);
            bool read();
            explicit operator bool();
            bool operator=(bool);
            bool read_no_change() const;

        private:
            bool __value;
        };
    };
}

#endif