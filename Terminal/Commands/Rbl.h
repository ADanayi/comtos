// In the name of Allah

#ifndef __COMTERM_RBMCOM_H
#define __COMTERM_RBMCOM_H

#include "../Command.h"

namespace comtos
{
    namespace terminal
    {
        namespace commands
        {
            class Rbl : public Command
            {
            public:
                explicit Rbl(){};

            protected:
                virtual const char *cname() override
                {
                    return "rbl";
                };
                virtual const char * help() override
                {
                    return "Usage: rbl [command]\n\rCommands Lists:\n\r\tlist or ls\n\r\tkill [runame]\n\r\tpause [runame]\n\r\tsched [runame]";
                };
                virtual CommandReturnT run(const char *argl) override;

                bool _ls(const char * argl);
                bool _kill(const char * argl);
                bool _pause(const char * argl);
                bool _sched(const char * argl);
            };
        };
    };
};

#endif