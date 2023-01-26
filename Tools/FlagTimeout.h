// In the name of Allah

#ifndef __COMTOS_FLAGTIMEOUT_H
#define __COMTOS_FLAGTIMEOUT_H

namespace comtos
{
    namespace tools
    {
        class FlagTimeout : protected Timeout
        {
        public:
            // explicit FlagTimeout() = delete;
            FlagTimeout(CoreBase *core = nullptr, const char * runame=nullptr, priorityT priority = priorityT::normal);
            scheduleResultT set(ticT timeout);
            terminateResultT reset();
            flagStateT flag();
            bool isSet();

            explicit operator bool();
            using Timeout::move_to_core;

        protected:
            virtual void on_timeout(ticT tic) override final;
            virtual void on_scheduled(ticT tic) override final;
            virtual void on_terminated(ticT tic) override final;

        private:
            flagStateT __flag;
        };
    };
};

#endif
