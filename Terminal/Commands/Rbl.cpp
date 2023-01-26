// In the name of Allah

#include "Rbl.h"
#include "../../comtos.h"

namespace comtos
{
    namespace terminal
    {
        namespace commands
        {
            CommandReturnT Rbl::run(const char *argl)
            {
                if (compareCurrentArg(argl, "ls") || compareCurrentArg(argl, "list"))
                {
                    if (_ls(argl))
                        return CommandReturnT::success;
                }
                else if (compareCurrentArg(argl, "kill"))
                {
                    if (_kill(fetchArgAndJump((char *)argl, nullptr)))
                        return CommandReturnT::success;
                }
                else if (compareCurrentArg(argl, "pause"))
                {
                    if (_pause(fetchArgAndJump((char *)argl, nullptr)))
                        return CommandReturnT::success;
                }
                else if (compareCurrentArg(argl, "sched"))
                {
                    if (_sched(fetchArgAndJump((char *)argl, nullptr)))
                        return CommandReturnT::success;
                }

                io->prln("rbl ran with errors...");
                io->prln(help());

                return CommandReturnT::error;
            };

            bool Rbl::_ls(const char *argl)
            {
                io->prln("List of scheduled runnables: ");
                Runnable **rtable = this->comterm->core()->_rtable();
                for (ridT rid = 0; rid < _COMT_MAX_RUNNABLES; rid++)
                {
                    Runnable *cursor = rtable[rid];
                    if (cursor == nullptr)
                        continue;
                    else
                    {
                        const char *runame = cursor->runame();
                        io->putCh('\t');
                        if (runame == nullptr)
                        {
                            io->pr("[no name]");
                        }
                        else
                        {
                            io->pr(runame);
                        }
                        io->putCh('\t');
                        io->pr(io->str(cursor->state()));
                        io->prln("");
                    }
                }
                return true;
            };

            bool Rbl::_kill(const char *argl)
            {
                fetchArgAndJump((char *)argl);
                if (argl == nullptr || argl[0] == '\0')
                    return false;
                Runnable *R = comterm->core()->findByRuname(argl);
                if (R == nullptr)
                {
                    io->pr("\tRunnable ");
                    io->pr(argl);
                    io->prln(" is not scheduled in the core.");
                    return true;
                }
                else
                {
                    if (comterm->core()->terminate_runnable(R) == terminateResultT::terminated)
                    {
                        io->prln("\t[Terminated]");
                    }
                    else
                    {
                        io->prln("\t[Not terminated]");
                    }
                    return true;
                }
            };

            bool Rbl::_pause(const char *argl)
            {
                fetchArgAndJump((char *)argl);
                if (argl == nullptr || argl[0] == '\0')
                    return false;
                Runnable *R = comterm->core()->findByRuname(argl);
                if (R == nullptr)
                {
                    io->pr("\tRunnable ");
                    io->pr(argl);
                    io->prln(" is not scheduled in the core.");
                    return true;
                }
                else
                {
                    if (comterm->core()->pause_runnable(R) == pauseResultT::paused)
                    {
                        io->prln("\t[Paused]");
                    }
                    else
                    {
                        io->prln("\t[Not Paused]");
                    }
                    return true;
                }
            };

            bool Rbl::_sched(const char *argl)
            {
                fetchArgAndJump((char *)argl);
                if (argl == nullptr || argl[0] == '\0')
                    return false;
                Runnable *R = comterm->core()->findByRuname(argl);
                if (R == nullptr)
                {
                    io->pr("\tRunnable ");
                    io->pr(argl);
                    io->prln(" is not scheduled in the core.");
                    return true;
                }
                else
                {
                    scheduleResultT ret = comterm->core()->schedule_runnable(R);
                    io->putCh('\t');
                    io->prln(io->str(ret));
                    return true;
                }
            };
        };
    };
};