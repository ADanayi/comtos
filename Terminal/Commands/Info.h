// In the name of Allah

#ifndef __COMTERM_INFOCOM_H
#define __COMTERM_INFOCOM_H

#include "../Command.h"

namespace comtos
{
    namespace terminal
    {
        namespace commands
        {
            class Info : public Command
            {
            public:
                explicit Info();

            protected:
                virtual const char *cname() override;
                virtual CommandReturnT run(const char *argl) override;
            };
        };
    };
};

#endif