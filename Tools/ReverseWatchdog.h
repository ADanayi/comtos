// In the name of Allah

#ifndef __COMTOS_REVERSE_WDG
#define __COMTOS_REVERSE_WDG

namespace comtos
{
    namespace tools
    {
        class ReverseWatchdog : private FlagTimeout
        {
        public:
            // explicit FlagTimeout() = delete;
            ReverseWatchdog(ticT T_risk, unsigned int N_risk = 1, CoreBase *core = nullptr, const char *runame = nullptr, priorityT priority = priorityT::normal);
            scheduleResultT start();
            terminateResultT stop();
            void clean();
            bool flag(); // Returns True if watchdog event detected
            unsigned int N_now();
            using FlagTimeout::move_to_core;

        private:
            const ticT T_risk;
            const unsigned int N_risk;
            unsigned int n;
        };
    };
};

#endif
