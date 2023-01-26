// In the name of Allah

#include "../comtos.h"

namespace comtos
{
    namespace tools
    {
        EventFlagRepeater::EventFlagRepeater(CoreBase *core, const char *runame, priorityT priority) : EventFlagTimeout(core, runame, priority)
        {
        };

        bool EventFlagRepeater::now() {
            bool n = EventFlagTimeout::now();
            if (n) EventFlagTimeout::postpone();
            return n;
        }

        EventFlagRepeater::operator bool() {
            return now();
        }
    };
};