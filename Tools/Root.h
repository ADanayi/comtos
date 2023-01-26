// In the name of Allah

#ifndef __COMTOS_TOOLS_ROOT_H
#define __COMTOS_TOOLS_ROOT_H

namespace comtos
{
    namespace tools
    {
        class RootInterval : public Interval
        {
        public:
            RootInterval(void(*setup)(), void (*loop)()) : Interval(
                                                                    0,
                                                                    nullptr,
                                                                    "root",
                                                                    true,
                                                                    priorityT::high)

            {
                __setup = setup;
                __loop = loop;
            };

        protected:
            void (*__setup)();
            void (*__loop)();
            virtual void on_scheduled(ticT tic) override
            {
                __setup();
            };
            virtual void on_interval(ticT tic) override
            {
                __loop();
            };
        };
    };
};

#endif
