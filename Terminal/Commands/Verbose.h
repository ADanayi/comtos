// In the name of Allah

#ifndef __COMTERM_VERBOSECOM_H
#define __COMTERM_VERBOSECOM_H

#include "../Command.h"

namespace comtos
{
    namespace terminal
    {
        namespace commands
        {
            class Verbose : public Command
            {
            public:
                explicit Verbose();

            protected:
                virtual const char *cname() override;
                virtual CommandReturnT run(const char *argl) override;
                virtual const char * help() override;
            };
        };
    };
};

#endif