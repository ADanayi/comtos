// In the name of Allah

#ifndef __COMTOS_TYPES_H
#define __COMTOS_TYPES_H

namespace comtos
{
    // Constants
    enum class runnableStateT
    {
        inited = 0x01,
        scheduled,
        running,
        scheduling,
        terminated,
        paused
    };

    enum class runnableExecTypeT
    {
        normal = 0x01,
        no_core = 0x02
    };

    enum class scheduleResultT
    {
        scheduled = 0x01,
        already_scheduled,
        no_space,
        no_core_submitted
    };

    enum class terminateResultT
    {
        terminated = 0x01,
        not_terminated = 0x02,
        unknown
    };

    enum class pauseResultT
    {
        paused = 0x01,
        not_paused,
        unknown
    };

    enum class runnableTicResultT
    {
        terminate_me,
        reschedule_me,
        continue_me,
        i_am_not_scheduled
    };

    enum class priorityT {
        normal = 0x00,
        high = 0x01
    };

    enum class flagStateT {
        reset = 0x00,
        set = 0x01,
        unknown
    };

    enum class requestResultT {
        declined = 0x00,
        accepted = 0x01
    };

    enum class errorT {
        core_is_null = 0x00,
        no_space_on_core,
        polling_loop,
        wrong_polling_finisher,
        unfinished_polling,
        wrong_polling_requester
    };

    enum class warningT {
        unfinished_polling = 0x01,
        no_space_on_core,
        pausing_pooler_not_allowed
    };

    enum class signalT {
        shutdown = 0x01,
    };

};

#endif
