// In the name of Allah

#ifndef __COMTOS_INTERVAL_H
#define __COMTOS_INTERVAL_H

// Body of Interval
namespace comtos
{
    class Interval : public Runnable
    {
    public:
        Interval(ticT interval = 0, CoreBase *core = nullptr, const char *runame = nullptr, bool auto_schedule = false, priorityT priority = priorityT::normal);
        void setInterval(ticT timeout = -1);
        virtual void on_interval(ticT tic) = 0;

    private:
        virtual runnableTicResultT __fire(ticT tic) override final;
        ticT t_interval;
    };

    class Finterval : public Interval
    {
    public:
        Finterval(void (*func)(ticT), ticT interval = 0, CoreBase *core = nullptr, const char *runame = nullptr, bool auto_schedule = false, priorityT priority = priorityT::normal) : Interval(interval, core, runame, auto_schedule, priority)
        {
            __func = func;
        }

        virtual void on_interval(ticT tic) override
        {
            __func(tic);
        }

    private:
        void (*__func)(ticT);
    };
}

#endif
