// In the name of Allah

#include "../comtos.h"

namespace comtos
{

    runnableTicResultT Interval::__fire(ticT tic)
    {
        on_interval(tic);
        return runnableTicResultT::reschedule_me;
    }

    void Interval::setInterval(ticT timeout)
    {
        t_delta = timeout;
    }

    Interval::Interval(ticT interval, CoreBase *core, const char *runame, bool auto_schedule, priorityT priority) : Runnable(core, runame, priority)
    {
        t_delta = interval;
        if (auto_schedule) {
            Runnable::reschedule();
        }
    };
}
