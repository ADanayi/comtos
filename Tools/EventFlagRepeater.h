// In the name of Allah

#ifndef __COMTOS_EVENTFLAGREPEATER_H
#define __COMTOS_EVENTFLAGREPEATER_H

namespace comtos
{
    namespace tools
    {
        class EventFlagRepeater : public EventFlagTimeout
        {
        public:
            // explicit FlagTimeout() = delete;
            EventFlagRepeater(CoreBase *core = nullptr, const char *runame = nullptr, priorityT priority = priorityT::normal);

            bool now();
            explicit operator bool();

        private:
            bool __has_read;
            ticT last_timeout;
        };
    };
};

#endif