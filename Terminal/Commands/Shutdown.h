// In the name of Allah

#ifndef __COMTERM_SHUTDOWNCOM_H
#define __COMTERM_SHUTDOWNCOM_H

#include "../Command.h"

namespace comtos
{
    namespace terminal
    {
        namespace commands
        {
            class Shutdown : public Command
            {
            public:
                explicit Shutdown() {};

            protected:
                virtual const char *cname() override
                {
                    return "shutdown";
                };
                virtual CommandReturnT run(const char *argl) override{
                    this->comterm->core()->signal(signalT::shutdown);
                    return CommandReturnT::success;
                };
            };
        };
    };
};

#endif