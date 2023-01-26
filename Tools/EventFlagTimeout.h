#ifndef __COMTOS_EVENTFLAGTIMEOUT_H
#define __COMTOS_EVENTFLAGTIMEOUT_H

namespace comtos
{
    namespace tools
    {
        class EventFlagTimeout : private FlagTimeout
        {
        public:
            // explicit FlagTimeout() = delete;
            EventFlagTimeout(CoreBase *core = nullptr, const char *runame = nullptr, priorityT priority = priorityT::normal);
            scheduleResultT set(ticT timeout);
            scheduleResultT postpone(); // Start measuring again with priviously used timeout, like cancel then start again
            terminateResultT cancel();
            scheduleResultT start(ticT timeout) {return set(timeout);}
            bool isRunning();
            using FlagTimeout::move_to_core;

            bool now();
            explicit operator bool();
            flagStateT _flag();
            bool _isSet();

        private:
            bool __has_read;
            ticT last_timeout;
        };
    };
};

#endif
