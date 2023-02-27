// In the name of Allah

#ifndef __COMTOS_CORE_H
#define __COMTOS_CORE_H

// Body of CoreBase
namespace comtos
{
    class CoreBase
    {
    private:
        static CoreBase *__singleton;

    public:
        static CoreBase *singleton();
        static void setActiveSingleton(CoreBase *cbase)
        {
            CoreBase::__singleton = cbase;
        }

    public:
        explicit CoreBase(CoreBase &) = delete;

        explicit CoreBase(ticT max_allowed_exectime);
        void boot(terminal::TIODriverBase *io = nullptr);

        bool has_space();
        bool runnable_is_scheduled(void *Runnable);
#ifndef _COMT_USE_MANUAL_MODE
        requestResultT join_loop();
#endif
        scheduleResultT schedule_runnable(void *Runnable);
        terminateResultT terminate_runnable(void *Runnable);
        pauseResultT pause_runnable(void *Runnable);
#ifdef _COMT_USE_MANUAL_MODE
        requestResultT initialize();
        requestResultT tic();
#endif

#ifdef _COMT_WATCH_TIME_VIOLATIONS
        requestResultT polling_request(void *R);
        void polling_finished(void *R);
        bool is_polling();
#endif
        Runnable *cursor();
        Runnable **_rtable();
        Runnable *findByRuname(const char *runame);

        void setWorkingPriority(priorityT P);
        priorityT workingPriority();
        void signal(signalT sig);

        virtual ticT ctic() = 0;

    protected:
        bool __full_tic(); // Returns false if should finish the loop else returns true
        virtual void on_initializing() = 0;
        virtual void on_singleton_changed() = 0;
        virtual void on_error(errorT) = 0;
#ifdef _COMT_WATCH_TIME_VIOLATIONS
        virtual void on_max_allowed_exectime_violation(Runnable *violated, ticT pureExectime, ticT pollingTime) = 0;
#endif
        virtual void on_warning(warningT);
        virtual void on_signal(signalT);

        virtual void on_schedule_request(Runnable *R);
        virtual void on_schedule_request_accepted(Runnable *R);
        virtual void on_main_loop_started();
        virtual void on_main_loop_finished();
        virtual void on_loop_iterated();
        virtual void on_cursor_iterated();

        Runnable *__cursor;
        Runnable *__polling_runnable;
        Runnable *__polling_func_requester;

        terminal::TIODriverBase *io;

    private:
        void __scan(Runnable *R, bool &has_space, bool &existing, ridT &first_empty_rid, ridT &target_rid);
        ridT __find_rid(Runnable *R);
        runnableTicResultT __exec_runnable(ridT rid);
        void __terminate_runnable(ridT rid);

        bool __joined;
        Runnable *rtable[_COMT_MAX_RUNNABLES];

        priorityT __wpriority;

        ticT __max_allowed_exectime;
        ticT __exectime_tic;
        ticT __pooling_start_tic;
        ticT __pooling_exectime_duration;
    };
};

#endif
