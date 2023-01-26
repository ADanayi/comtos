// In the name of Allah

#include "../comtos.h"

namespace comtos
{

    runnableTicResultT Timeout::__fire(ticT tic) {
        on_timeout(tic);
        return runnableTicResultT::terminate_me;
    }

    scheduleResultT Timeout::reschedule(ticT timeout) {
        if (timeout != -1) {
            t_delta = timeout;
        }
        return Runnable::reschedule();
    }

    Timeout::Timeout(ticT timeout, CoreBase * core, const char *runame, bool auto_schedule, priorityT priority): Runnable(core, runame, priority) {
        t_delta = timeout;
        if (auto_schedule) {
            Runnable::reschedule();
        }
    };
}
