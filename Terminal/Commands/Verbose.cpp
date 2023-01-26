// In the name of Allah

#include "../Command.h"
#include "Verbose.h"

namespace comtos
{
    namespace terminal
    {
        namespace commands
        {

            Verbose::Verbose(){};

            const char *Verbose::cname()
            {
                return "verbose";
            };

            const char *Verbose::help()
            {
                return "Usage: Use on/off/status or say [string].";
            };

            CommandReturnT Verbose::run(const char *argl)
            {
                if (compareCurrentArg(argl, "on"))
                {
                    io->setVerbosing(true);
                    io->prln("verbose on");
                }
                else if (compareCurrentArg(argl, "off"))
                {
                    io->setVerbosing(false);
                    io->prln("verbose off");
                }
                else if (compareCurrentArg(argl, "status"))
                {
                    io->pr("verbosing is ");
                    if (io->getVerbosing())
                        io->prln("on");
                    else
                        io->prln("off");
                }
                else if (compareCurrentArg(argl, "say"))
                {
                    const char *txt = fetchArgAndJump((char *)argl);
                    if (txt == nullptr)
                    {
                        io->prln(help());
                        return CommandReturnT::error;
                    }
                    io->vprln(txt);
                }
                else
                {
                    io->prln(help());
                    return CommandReturnT::error;
                }
                return CommandReturnT::success;
            };

        };
    };
};
