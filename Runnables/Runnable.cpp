// In the name of Allah

#include "../comtos.h"

namespace comtos
{
    Runnable::Runnable(const char *runame, priorityT priority)
    {
        __runame = runame;
        __core = CoreBase::singleton();
        __state = runnableStateT::inited;
        __priority = priority;
        __execType = runnableExecTypeT::normal;
    };

    const char *Runnable::_runame()
    {
        return this->__runame;
    }

    const char *Runnable::runame()
    {
        if (__runame == nullptr)
            return "";
        return this->__runame;
    }

    void Runnable::move_to_core(CoreBase *core)
    {
        __core = core;
    }

    Runnable::Runnable(CoreBase *core, const char *runame, priorityT priority)
    {
        __runame = runame;
        __core = nullptr;
        __state = runnableStateT::inited;
        __priority = priority;
        if (core == nullptr)
        {
            __core = CoreBase::singleton();
        }
        else
            __core = core;
        __execType = runnableExecTypeT::normal;
    };

    CoreBase *Runnable::core()
    {
        if (__execType == runnableExecTypeT::no_core)
            return nullptr;

        if (__core == nullptr)
        {
            // CoreBase::captureSingleton(__core);
            __core = CoreBase::singleton();
        }
        return __core;
    }

    priorityT Runnable::priority()
    {
        return __priority;
    }

    void Runnable::setPriority(priorityT p)
    {
        __priority = p;
    }

    terminateResultT Runnable::terminate()
    {
        if (core() == nullptr)
        {
            return terminateResultT::unknown;
        }
        else
            return core()->terminate_runnable(this);
    }

    runnableTicResultT Runnable::__fire(ticT)
    {
        return runnableTicResultT::terminate_me;
    }

    void Runnable::on_scheduled(ticT){};
    void Runnable::on_terminated(ticT){};
    void Runnable::on_paused(ticT){};
#ifdef _COMT_WATCH_TIME_VIOLATIONS
    requestResultT Runnable::on_polling_request(Runnable *requesting)
    {
        return requestResultT::accepted;
    };
    void Runnable::on_polling_finished(Runnable *requesting){};

    requestResultT Runnable::polling_request()
    {
        if (__execType == runnableExecTypeT::no_core)
            return requestResultT::accepted;

        return this->core()->polling_request(this);
    }

    void Runnable::polling_finished()
    {
        if (__execType == runnableExecTypeT::no_core)
            return;
        return this->core()->polling_finished(this);
    }
#endif

    scheduleResultT Runnable::reschedule()
    {
        if (this->core() == nullptr)
        {
            return scheduleResultT::no_core_submitted;
        }
        return core()->schedule_runnable(this);
    }

    runnableStateT Runnable::state()
    {
        return this->__state;
    }

    runnableTicResultT Runnable::__tic(ticT toc)
    {
        __state = runnableStateT::scheduling;
        if (toc - this->__t_tic >= this->t_delta)
        {
            __state = runnableStateT::running;
            runnableTicResultT ret = __fire(toc);
            // This condition is here to check if the runnable state is not changed during executing it...
            if (__state == runnableStateT::running)
            {
                __state = runnableStateT::scheduling;
            }
            return ret;
        }
        return runnableTicResultT::continue_me;
    }

    void Runnable::_run_no_core(ticT (*ctic)())
    {
        __execType = runnableExecTypeT::no_core;
        on_scheduled(ctic());
        while (1)
        {
            if (__state == runnableStateT::paused)
                continue;

            runnableTicResultT ticResult = __tic(ctic());

            if (__state != runnableStateT::scheduling)
                continue;

            if ((ticResult == runnableTicResultT::continue_me) || (ticResult == runnableTicResultT::reschedule_me))
            {
                this->__state == runnableStateT::scheduled;
            }
            else
            {
                break;
            }
        }
        on_terminated(ctic());
    };
};
