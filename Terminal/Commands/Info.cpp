// In the name of Allah

#include "Info.h"

namespace comtos
{
    namespace terminal
    {
        namespace commands
        {
            Info::Info(){

            };

            const char *Info::cname()
            {
                return "info";
            };

            CommandReturnT Info::run(const char *argl)
            {
                io->prln("COMTERM v1.0 (2022) by Abolfazl Danayi.");
                return CommandReturnT::success;
            };
        };
    };
};