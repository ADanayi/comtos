// In the name of Allah

// #ifndef __COMTOS_FLAGTIMEOUT_H
// #define __COMTOS_FLAGTIMEOUT_H

#include "../comtos.h"

namespace comtos
{
    namespace tools
    {
        FlagTimeout::FlagTimeout(CoreBase *core, const char *runame, priorityT priority) : Timeout(0, core, runame, false, priority)
        {
            __flag = flagStateT::reset;
        }

        flagStateT FlagTimeout::flag()
        {
            return __flag;
        }

        bool FlagTimeout::isSet()
        {
            return __flag == flagStateT::set;
        }

        void FlagTimeout::on_scheduled(ticT tic)
        {
            __flag = flagStateT::set;
        }

        void FlagTimeout::on_terminated(ticT tic)
        {
            __flag = flagStateT::reset;
        }

        void FlagTimeout::on_timeout(ticT tic)
        {
            __flag = flagStateT::reset;
        }

        terminateResultT FlagTimeout::reset()
        {
            terminateResultT ret = terminate();
            return ret;
        }

        scheduleResultT FlagTimeout::set(ticT timeout)
        {
            scheduleResultT ret = reschedule(timeout);
            return ret;
        }

        FlagTimeout::operator bool()
        {
            return this->isSet();
        }
    };
};

// #endif
