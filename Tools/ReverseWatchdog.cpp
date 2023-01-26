#include "../comtos.h"

namespace comtos
{
    namespace tools
    {
        ReverseWatchdog::ReverseWatchdog(ticT T_risk, unsigned int N_risk, CoreBase *core, const char *runame, priorityT priority) : FlagTimeout(core, runame, priority),
                                                                                                                                     N_risk(N_risk),
                                                                                                                                     T_risk(T_risk)
        {
        };

        scheduleResultT ReverseWatchdog::start()
        {
            n = 0;
            return FlagTimeout::set(T_risk);
        };

        terminateResultT ReverseWatchdog::stop()
        {
            n = 0;
            return FlagTimeout::reset();
        }

        void ReverseWatchdog::clean()
        {
            n = 0;
            FlagTimeout::reset();
            FlagTimeout::set(T_risk);
        }

        unsigned int ReverseWatchdog::N_now()
        {
            return n;
        }

        bool ReverseWatchdog::flag()
        {
            if (FlagTimeout::isSet())
            {
                n++;
            }
            else
            {
                n = 0;
                FlagTimeout::reset();
            }
            FlagTimeout::set(T_risk);
            if (n >= N_risk)
            {
                n = N_risk;
                return true;
            }
            return false;
        }
    };
};

// #endif
