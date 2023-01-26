// In the name of Allah

#include "../comtos.h"

namespace comtos
{
    namespace tools
    {
        EventFlagTimeout::EventFlagTimeout(CoreBase *core, const char *runame, priorityT priority) : FlagTimeout(core, runame, priority)
        {
            __has_read = true;
            last_timeout = 0;
        };

        scheduleResultT EventFlagTimeout::set(ticT timeout)
        {
            scheduleResultT r = FlagTimeout::set(timeout);
            if (FlagTimeout::isSet())
            {
                __has_read = false;
                last_timeout = timeout;
            }
            // __has_read = false;
            return r;
        };

        scheduleResultT EventFlagTimeout::postpone()
        {
            cancel();
            return set(last_timeout);
        }

        terminateResultT EventFlagTimeout::cancel()
        {
            terminateResultT r;
            if (FlagTimeout::isSet())
                r = FlagTimeout::reset();
            else
                r = terminateResultT::terminated;
            if (FlagTimeout::flag() == flagStateT::reset)
            {
                __has_read = true;
            }
            return r;
        };

        bool EventFlagTimeout::_isSet()
        {
            return FlagTimeout::isSet();
        }

        flagStateT EventFlagTimeout::_flag()
        {
            return FlagTimeout::flag();
        }

        bool EventFlagTimeout::isRunning()
        {
            if (__has_read)
                return false;
            else
            {
                if (!FlagTimeout::isSet())
                {
                    return true;
                }
                return false;
            }
        }

        bool EventFlagTimeout::now()
        {
            if (__has_read)
                return false;
            else
            {
                if (!FlagTimeout::isSet())
                {
                    __has_read = true;
                    return true;
                }
                return false;
            }
        }

        EventFlagTimeout::operator bool()
        {
            return now();
        }
    };
}