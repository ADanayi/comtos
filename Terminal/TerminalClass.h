// In the name of Allah

#ifndef __COMTOS_TERM_BASE_H
#define __COMTOS_TERM_BASE_H

#include "types.h"
#include "TIODriverBase.h"
#include "Command.h"

namespace comtos
{
    namespace terminal
    {
        class Terminal : public Interval
        {
        public:
            explicit Terminal(Terminal &) = delete;
            explicit Terminal(TIODriverBase *io, bool echo = true, ticT interval = 0, CoreBase *core = nullptr, priorityT priority = priorityT::normal);

            static bool __is_ending_ch(char &ch);
            static bool __is_content_ch(char &ch);

            void install_command(Command *command);

        protected:
            TIODriverBase *io;
            Command *com_head;
            Command *com_tail;

            virtual void on_scheduled(ticT tic) override;
            virtual void on_interval(ticT tic) override;
#ifdef _COMT_WATCH_TIME_VIOLATIONS
            virtual requestResultT on_polling_request(Runnable *requesting) override;
#endif
            bool __pr_at_line_header;
            bool __pr_printed_with_pooling;
            void __pr_line_header(bool force_newline = false, bool pooling = false);
            void echo();

            void _start_command();

            static const char *__cname_match(Command *com, const char *cname); // not matched -> nullptr, matched -> starting argl

        private:
            TerminalStateT state;
            unsigned char buf[_COMT_TERMINAL_BUF_SIZE];
            unsigned char buf_ctr;
            bool __echo;
        };
    };
};

#endif
