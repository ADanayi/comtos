// In the name of Allah

#include "../comtos.h"

namespace comtos
{
    namespace terminal
    {
        Terminal::Terminal(TIODriverBase *io, bool echo, ticT interval, CoreBase *core, priorityT priority) : Interval(interval, core, "comterm", false, priority)
        {
            this->io = io;
            com_head = nullptr;
            com_tail = nullptr;
            state = TerminalStateT::idle;
            buf_ctr = 0;
            buf[0] = '\0';
            __pr_at_line_header = false;
            this->__echo = echo;
            io->prln("\n\rWelcome to COMTOS");
            io->prln("Terminal Started");
            io->prln("COMTERM v1.0 (2022)");
        }

        void Terminal::__pr_line_header(bool force_new_line, bool pooling)
        {
            if (force_new_line)
            {
                io->putCh('\n');
                io->putCh('\r');
            }
            bool full_redraw = pooling != __pr_printed_with_pooling;
            if (full_redraw)
            {
                io->putCh('\r');
            }
            if (!__pr_at_line_header || force_new_line || full_redraw)
            {
                io->pr("root@comterm");
                if (pooling)
                {
                    io->putCh('!');
                }
                else
                {
                    io->putCh('$');
                }
                io->putCh(' ');
                __pr_at_line_header = true;
                if (full_redraw)
                    io->pr((const char *)buf);
            }
            __pr_printed_with_pooling = pooling;
        };

        void Terminal::on_scheduled(ticT t){};

        void Terminal::_start_command()
        {
            state = TerminalStateT::joined_command;

            io->newline();
            __pr_at_line_header = false;
            if (com_head == nullptr)
            {
                io->prln("No command installed.");
            }
            else
            {
                Command *cursor = com_head;
                Command *target = nullptr;
                while (true)
                {
                    if (cursor == nullptr)
                    {
                        io->prln("Bad command name or command not installed.");
                        break;
                    }
                    const char *argl = __cname_match(cursor, (const char *)buf);
                    if (argl == nullptr)
                    {
                        cursor = (Command *)cursor->next;
                        continue;
                    }
                    else
                    {
#ifdef _COMT_WATCH_TIME_VIOLATIONS
                        if (polling_request() == comtos::requestResultT::accepted)
                        {
#endif
                            cursor->run(Command::jumpToArg(argl));
#ifdef _COMT_WATCH_TIME_VIOLATIONS
                            polling_finished();
                        }
#endif
                        break;
                    }
                };
            }

            buf[0] = '\0';
            buf_ctr = 0;
            state = TerminalStateT::idle;
        }

        const char *Terminal::__cname_match(Command *com, const char *cname)
        {
            const char *dcname = com->cname();
            if ((dcname[0] == '\0') || (cname[0] == '\0'))
                return nullptr;

            int ctr = 0;
            while (true)
            {
                if (dcname[ctr] == '\0')
                {
                    if (cname[ctr] == '\0')
                        return "";
                    else if (cname[ctr] == ' ')
                        return (cname + ctr + 1);
                    else
                        return nullptr;
                }
                else if (dcname[ctr] != cname[ctr])
                    return nullptr;
                ctr++;
            }
            return nullptr;
        }

        void Terminal::install_command(Command *command)
        {
            command->prev = com_tail;
            command->next = nullptr;

            if (com_head == nullptr)
                com_head = command;

            if (com_tail != nullptr)
            {
                com_tail->next = command;
            }

            com_tail = command;

            command->__install(this->io, this);

            io->pr("command ");
            io->pr(command->cname());
            io->prln(" installed.");
        };

        void Terminal::echo()
        {
            if (__echo)
            {
                io->echo_last_char();
            }
        }

#ifdef _COMT_WATCH_TIME_VIOLATIONS
        requestResultT Terminal::on_polling_request(Runnable *requesting)
        {
            if (state != TerminalStateT::joined_command)
            {
                __pr_line_header(false, true);
            }
            return requestResultT::accepted;
        };
#endif

        void Terminal::on_interval(ticT tic)
        {
            switch (state)
            {
            case TerminalStateT::idle:
                __pr_line_header(false, false);
                if (io->hasCh())
                {
                    char ch = io->getCh();
                    if (__is_content_ch(ch))
                    {
                        if (ch == 3)
                        {
                            io->prln("CTRL+C does not work here! Use the shutdown command.");
                            __pr_line_header(true, false);
                            return;
                        }
                        if (ch == '\t')
                            return;
                        buf[0] = ch;
                        buf_ctr = 1;
                        buf[buf_ctr] = '\0';
                        echo();
                        state = TerminalStateT::getting_input;
                    }
                    else
                    {
                        break;
                    }
                }
                break;
            case TerminalStateT::getting_input:
                if (io->hasCh())
                {
                    char ch = io->getCh();
                    if (ch == 3)
                    {
                        io->pr(" CTRL+C");
                        __pr_line_header(true, false);
                        state = TerminalStateT::idle;
                        buf_ctr = 0;
                    };
                    if (!__is_ending_ch(ch) && (buf_ctr != _COMT_TERMINAL_BUF_SIZE))
                    {
                        if (__is_content_ch(ch))
                        {
                            if (ch == '\t')
                            {
                                if ((buf[buf_ctr - 1] == '\0') || (buf[buf_ctr - 1] == ' '))
                                    return;
                                ch = ' ';
                                io->last_read_char = ' ';
                            }
                            buf[buf_ctr] = ch;
                            buf_ctr += 1;
                            buf[buf_ctr] = '\0';
                        }
                        else if (ch == '\b')
                        {
                            buf_ctr--;
                            buf[buf_ctr] = '\0';
                            if (buf_ctr == 0)
                            {
                                state = TerminalStateT::idle;
                            }
                        }
                        echo();
                    }
                    else
                    {
                        _start_command();
                    }
                }

            default:
                break;
            }
        }

        bool Terminal::__is_ending_ch(char &ch)
        {
            return (ch == '\n') || (ch == '\r');
        };

        bool Terminal::__is_content_ch(char &ch)
        {
            return (!__is_ending_ch(ch) && (ch != '\b'));
        };
    };
}; // namespace  comtos
