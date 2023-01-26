// In the name of Allah

#ifndef __CLOCK_H
#define __CLOCK_H

#include "../comtos.h"

namespace comtos
{
    namespace tools
    {
        class Clock
        {
        public:
            explicit Clock() = delete;
            explicit Clock(Clock &clk)
            {
                this->core = clk.core;
            };
            explicit Clock(comtos::CoreBase *core)
            {
                this->core = core;
                __tic = now();
            };
            ticT now()
            {
                return core->ctic();
            }
            void wait(ticT duration)
            {
                ticT t = now();
                while (now() - t < duration)
                {
                };
            }
            ticT tic()
            {
                __tic = now();
                return __tic;
            }
            ticT toc()
            {
                return now() - __tic;
            }

        private:
            comtos::CoreBase *core;
            ticT __tic;
        };
    };
};

#endif
