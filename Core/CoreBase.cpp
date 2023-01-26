// In the name of Allah

#include "../comtos.h"

namespace comtos
{
    CoreBase *CoreBase::__singleton = nullptr;

    CoreBase *CoreBase::singleton()
    {
        return __singleton;
    }

    // void CoreBase::on_initializing(){};
    // void CoreBase::on_error(errorT){};
    // void CoreBase::on_singleton_changed(){};

    CoreBase::CoreBase(ticT max_allowed_exectime)
    {
        __max_allowed_exectime = max_allowed_exectime;
        this->io = nullptr;
    }

    void CoreBase::on_schedule_request(Runnable *R) { return; };
    void CoreBase::on_schedule_request_accepted(Runnable *R){};
    void CoreBase::on_loop_iterated(){};
    void CoreBase::on_main_loop_started(){};
    void CoreBase::on_main_loop_finished(){};

    void CoreBase::boot(terminal::TIODriverBase *io)
    {
        on_initializing();
        for (ridT rid = 0; rid < _COMT_MAX_RUNNABLES; rid++)
        {
            rtable[rid] = nullptr;
        }
        if (CoreBase::__singleton != this)
        {
            CoreBase::__singleton = this;
            on_singleton_changed();
        }
        this->__joined = false;
        this->__polling_runnable = nullptr;
        this->__wpriority = priorityT::normal;
        this->io = io;
    }

    void CoreBase::setWorkingPriority(priorityT p)
    {
        __wpriority = p;
    }

    Runnable *CoreBase::cursor()
    {
        return __cursor;
    }

    Runnable **CoreBase::_rtable()
    {
        return rtable;
    }

    Runnable *CoreBase::findByRuname(const char *runame)
    {
        if ((runame[0] == '\0') || (runame == nullptr))
            return nullptr;

        for (ridT rid = 0; rid < _COMT_MAX_RUNNABLES; rid++)
        {
            Runnable *R = rtable[rid];
            if (R == nullptr)
                continue;
            if (R->__runame == nullptr)
                continue;
            int i = 0;
            const char *runame2 = R->__runame;
            bool matched = true;
            while (1)
            {
                if (runame[i] != runame2[i])
                {
                    matched = false;
                    break;
                }
                if (runame[i] == '\0')
                    break;
                i++;
            }
            if (matched)
                return R;
        }
        return nullptr;
    }

    void CoreBase::signal(signalT sig)
    {
        switch (sig)
        {
        case signalT::shutdown:
            this->__joined = false;
            break;

        default:
            break;
        }
    };
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#ifndef _COMT_USE_MANUAL_MODE
    requestResultT
    CoreBase::join_loop()
    {
        if (this->__joined)
            return requestResultT::declined;
        this->__joined = true;
        bool isMainLoop = true; // For future considerations
        if (isMainLoop)
            on_main_loop_started();
        while (this->__joined && __full_tic())
        {
            // Wait for the last __full_tic!
        }
        this->__joined = false;
        if (isMainLoop)
            on_main_loop_finished();
        return requestResultT::accepted;
    }
#endif

    bool CoreBase::__full_tic()
    {
        Runnable *cursor;
        bool finish = true;
        for (ridT rid = 0; (rid < _COMT_MAX_RUNNABLES) && __joined; rid++)
        {
            if (__polling_runnable != nullptr)
            {
                on_error(errorT::unfinished_polling);
            }
            cursor = rtable[rid];
            if (cursor != nullptr)
            {
                finish = false;
                if (cursor->__priority < __wpriority)
                    continue;
                if (cursor->__state == runnableStateT::paused)
                    continue;
                runnableTicResultT exec_result = __exec_runnable(rid);
                // Runnable state changed during the execution, so no need to reschedule it.
                if (cursor->__state != runnableStateT::scheduling)
                    continue;
                switch (exec_result)
                {
                case runnableTicResultT::reschedule_me:
                    rtable[rid]->__state = runnableStateT::scheduled;
                    rtable[rid]->__t_tic = ctic();
                    break;
                case runnableTicResultT::continue_me:
                    rtable[rid]->__state = runnableStateT::scheduled;
                    break;
                case runnableTicResultT::i_am_not_scheduled:
                case runnableTicResultT::terminate_me:
                default:
                    __terminate_runnable(rid);
                }
            }
        }
        on_loop_iterated();
        return !finish;
    }

#ifdef _COMT_USE_MANUAL_MODE
    requestResultT CoreBase::initialize()
    {
        __joined = true;
        return requestResultT::accepted;
    }

    requestResultT CoreBase::tic()
    {
        __full_tic();
        return requestResultT::accepted;
    }
#endif

    /////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////

#ifdef _COMT_WATCH_TIME_VIOLATIONS
    requestResultT CoreBase::polling_request(void *runnable)
    {
        // Checking if not already polling
        Runnable *R = (Runnable *)runnable;
        __polling_func_requester = R;
        if (this->__polling_runnable != nullptr)
        {
            on_error(errorT::polling_loop);
            return requestResultT::declined;
        }

        // Checking if allowed to poll
        if (R != __cursor)
        {
            on_error(errorT::wrong_polling_requester);
            return requestResultT::declined;
        }

        // Voting
        Runnable *cursor;
        for (ridT rid = 0; rid < _COMT_MAX_RUNNABLES; rid++)
        {
            cursor = rtable[rid];
            if (cursor != nullptr & cursor != R)
            {
                if (cursor->on_polling_request(R) != requestResultT::accepted)
                    return requestResultT::declined;
            }
        }
        this->__polling_runnable = R;
        __pooling_start_tic = ctic();
        return requestResultT::accepted;
    }

    void CoreBase::polling_finished(void *runnable)
    {
        Runnable *R = (Runnable *)runnable;
        __polling_func_requester = R;
        Runnable *cursor;
        if (this->__polling_runnable == R)
        {
            __polling_runnable = nullptr;
            for (ridT rid = 0; rid < _COMT_MAX_RUNNABLES; rid++)
            {
                cursor = rtable[rid];
                if (cursor != nullptr && cursor != R)
                {
                    cursor->on_polling_finished(R);
                }
            }
        }
        else
        {
            on_error(errorT::wrong_polling_finisher);
            return;
        }
        __pooling_exectime_duration += ctic() - __pooling_start_tic;
    }
#endif

    void CoreBase::on_warning(warningT w){};

    void CoreBase::on_signal(signalT){};

    bool CoreBase::has_space()
    {
        for (ridT rid = 0; rid < _COMT_MAX_RUNNABLES; rid++)
        {
            if (rtable[rid] == nullptr)
                return true;
        }
        return false;
    }

    bool CoreBase::runnable_is_scheduled(void *runnable)
    {
        Runnable *R = (Runnable *)runnable;
        for (ridT rid = 0; rid < _COMT_MAX_RUNNABLES; rid++)
        {
            if (rtable[rid] == R)
                return true;
        }
        return false;
    }

    scheduleResultT CoreBase::schedule_runnable(void *runnable)
    {
        Runnable *R = (Runnable *)runnable;
        ridT empty_rid, target_rid;
        bool has_space, existing = false;
        on_schedule_request(R);
        __scan(R, has_space, existing, empty_rid, target_rid);
        if (existing)
        {
            if (R->__state != runnableStateT::scheduled)
            {
                on_schedule_request_accepted(R);
                R->__core = this;
                R->__state = runnableStateT::scheduled;
                R->__t_tic = ctic();
                R->on_scheduled(ctic());
                return scheduleResultT::scheduled;
            }
            return scheduleResultT::already_scheduled;
        }
        else
        {
            if (has_space & R != nullptr)
            {
                on_schedule_request_accepted(R);
                rtable[empty_rid] = R;
                R->__core = this;
                R->__state = runnableStateT::scheduled;
                R->__t_tic = ctic();
                R->on_scheduled(ctic());
                return scheduleResultT::scheduled;
            }
        }
        on_error(errorT::no_space_on_core);
        return scheduleResultT::no_space;
    }

    ridT CoreBase::__find_rid(Runnable *R)
    {
        for (ridT rid = 0; rid < _COMT_MAX_RUNNABLES; rid++)
        {
            if (rtable[rid] == R)
            {
                return rid;
            }
        }
        return _COMT_MAX_RUNNABLES;
    }

    terminateResultT CoreBase::terminate_runnable(void *runnable)
    {
        Runnable *R = (Runnable *)runnable;
        ridT rid = __find_rid(R);
        if (rid == _COMT_MAX_RUNNABLES)
        {
            R->__state = runnableStateT::terminated;
            terminateResultT::terminated;
        };
        __terminate_runnable(rid);
        return terminateResultT::terminated;
    }

    pauseResultT CoreBase::pause_runnable(void *runnable)
    {
        Runnable *R = (Runnable *)runnable;
        if (R == __polling_runnable)
        {
            on_warning(warningT::pausing_pooler_not_allowed);
            return pauseResultT::not_paused;
        }
        ridT rid = __find_rid(R);
        if (rid == _COMT_MAX_RUNNABLES)
        {
            R->__state = runnableStateT::terminated;
            return pauseResultT::unknown;
        };
        R->__state = runnableStateT::paused;
        return pauseResultT::paused;
    }

    priorityT CoreBase::workingPriority()
    {
        return __wpriority;
    }

    void CoreBase::__scan(Runnable *R, bool &has_space, bool &existing, ridT &first_empty_rid, ridT &target_rid)
    {
        has_space = false;
        existing = false;
        for (ridT rid = 0; rid < _COMT_MAX_RUNNABLES; rid++)
        {
            if ((rtable[rid] == nullptr) & !has_space)
            {
                has_space = true;
                first_empty_rid = rid;
                return;
            }
            else if ((rtable[rid] == R))
            {
                existing = true;
                target_rid = rid;
            }
        }
    }

#ifdef _COMT_WATCH_TIME_VIOLATIONS
    bool CoreBase::is_polling()
    {
        return __polling_runnable != nullptr;
    }
#endif

    runnableTicResultT CoreBase::__exec_runnable(ridT rid)
    {
        Runnable *R = rtable[rid];
        __cursor = R;
        if (R == nullptr)
            return runnableTicResultT::i_am_not_scheduled;

        __exectime_tic = ctic();
        __pooling_exectime_duration = 0;
        runnableTicResultT ticResult;
        if (R->__state == runnableStateT::scheduled)
        {
            ticResult = R->__tic(ctic());
        }
        else
            ticResult = runnableTicResultT::i_am_not_scheduled;
#ifdef _COMT_WATCH_TIME_VIOLATIONS
        if (__polling_runnable != nullptr)
        {
            on_warning(warningT::unfinished_polling);
            polling_finished(R);
        }
        ticT execTime = ctic() - __exectime_tic - __pooling_exectime_duration;
        if (execTime > __max_allowed_exectime)
        {
            on_max_allowed_exectime_violation(R, execTime, __pooling_exectime_duration);
        }
#endif
        __cursor = nullptr;
        return ticResult;
    }

    void CoreBase::__terminate_runnable(ridT rid)
    {
        if (rtable[rid] != nullptr)
        {
            Runnable *R = rtable[rid];
            R->__state = runnableStateT::terminated;
            rtable[rid] = nullptr;
            R->on_terminated(ctic());
        }
    }
};