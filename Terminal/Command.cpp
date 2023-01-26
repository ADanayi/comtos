// In the name of Allah

#include "Command.h"

namespace comtos
{
    namespace terminal
    {
        Command::Command()
        {
            this->io = nullptr;
        }

        void Command::__install(TIODriverBase *io, Terminal *t)
        {
            this->io = io;
            this->comterm = t;
        }

        const char *Command::help()
        {
            return "No help available for this command.";
        }
        bool Command::compareCurrentArg(const char *argl, const char *val)
        {
            int ctr = 0;
            char cha, chv;
            argl = jumpToArg(argl);
            if ((argl == nullptr) || (argl[ctr] == '\0') || (val[ctr] == '\0'))
                return false;
            while (true)
            {
                cha = argl[ctr];
                chv = val[ctr];

                if (chv == '\0')
                {
                    if ((cha == ' ') || (cha == '\0'))
                        return true;
                    else
                        return false;
                }
                else
                {
                    if (chv != cha)
                        return false;
                }
                ctr++;
            }
            return false;
        }

        const char *Command::fetchArgAndJump(char *argl, const char *defaultEnd)
        {
            char ch;
            argl = (char *)jumpToArg(argl);
            if ((argl == nullptr) || (argl == defaultEnd))
                return defaultEnd;
            while (true)
            {
                argl++;
                ch = *argl;
                if (ch == '\0')
                    return defaultEnd;
                if ((ch == ' ') || (ch == '\t'))
                {
                    *argl = '\0';
                    argl++;
                    return jumpToArg(argl);
                };
            };
        }

        const char *Command::jumpToArg(const char *argl, const char *defaultEnd)
        {
            int ctr = 0;
            char ch;
            if ((argl == nullptr) || (argl == defaultEnd))
                return defaultEnd;
            while (true)
            {
                ch = argl[ctr];
                if (ch == '\0')
                    return defaultEnd;
                if ((ch == ' ') || (ch == '\t'))
                    ctr++;
                else
                    return (argl + ctr);
            }
        }
    };
};