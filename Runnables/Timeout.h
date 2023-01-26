// In the name of Allah

#ifndef __COMTOS_TIMEOUT_H
#define __COMTOS_TIMEOUT_H

// Body of Timeout
namespace comtos
{
    class Timeout : public Runnable
    {
    public:
        Timeout(ticT timeout, CoreBase *core = nullptr, const char *runame = nullptr, bool auto_schedule = true, priorityT priority = priorityT::normal);
        scheduleResultT reschedule(ticT timeout = -1);
        virtual void on_timeout(ticT tic) = 0;

    private:
        virtual runnableTicResultT __fire(ticT tic) override final;
    };

};

#endif
