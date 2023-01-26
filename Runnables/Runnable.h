// In the name of Allah

#ifndef __COMOTS_RUNNABLE_H
#define __COMOTS_RUNNABLE_H

// Body of Runnable
namespace comtos
{
    class Runnable
    {
        friend class CoreBase;

    public:
        explicit Runnable() = delete;
        explicit Runnable(Runnable &) = delete;
        Runnable(const char *runame = nullptr, priorityT priority = priorityT::normal);
        Runnable(CoreBase *core, const char *runame = nullptr, priorityT priority = priorityT::normal);
        runnableStateT state();
        priorityT priority();
        void setPriority(priorityT p);
        CoreBase *core();
        const char *runame();  // This function is similar to _runame, but converts nullptr to ""
        const char *_runame(); // This function returns the real runame
        void _run_no_core(ticT (*ctic)());
        void move_to_core(CoreBase *core);

    protected:
        virtual runnableTicResultT __tic(ticT tic);
        virtual runnableTicResultT __fire(ticT tic);
#ifdef _COMT_WATCH_TIME_VIOLATIONS
        requestResultT polling_request();
        void polling_finished();
        virtual requestResultT on_polling_request(Runnable *requesting);
        virtual void on_polling_finished(Runnable *requesting);
#endif
        virtual void on_scheduled(ticT tic);
        virtual void on_terminated(ticT tic);
        virtual void on_paused(ticT tic);
        scheduleResultT reschedule();
        terminateResultT terminate();
        runnableStateT __state;
        ticT __t_tic;
        ticT t_delta;
        priorityT __priority;
        const char *__runame;

        runnableExecTypeT __execType;

    private:
        CoreBase *__core;
    };
};

#endif
