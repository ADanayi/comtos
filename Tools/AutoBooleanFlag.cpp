// In the name of Allah

#include "AutoBooleanFlag.h"
namespace comtos
{
    namespace tools
    {
        AutoBooleanFlag::AutoBooleanFlag()
        {
            __value = false;
        }

        void AutoBooleanFlag::set(bool value)
        {
            __value = value;
        }

        bool AutoBooleanFlag::read()
        {
            if (__value)
            {
                __value = false;
                return true;
            }
            return false;
        }

        AutoBooleanFlag::operator bool()
        {
            return read();
        }

        bool AutoBooleanFlag::operator=(bool b)
        {
            set(b);
            return b;
        }

        bool AutoBooleanFlag::read_no_change() const
        {
            return __value;
        }
    };
};
