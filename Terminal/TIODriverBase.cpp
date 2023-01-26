// In the name of Allah

#include "TIODriverBase.h"

namespace comtos
{
    namespace terminal
    {
        TIODriverBase::TIODriverBase()
        {
            last_read_char = '\0';
            verbosing = false;
            warning = true;
            singleton = this;
        };

        void TIODriverBase::pr(const char *str)
        {
            int ctr = 0;
            while (str[ctr] != '\0')
            {
                putCh(str[ctr]);
                ctr++;
            }
        };

        void TIODriverBase::prln(const char *str)
        {
            pr(str);
            newline();
        }

        void TIODriverBase::newline()
        {
            putCh('\n');
            putCh('\r');
        }

        void TIODriverBase::echo_last_char()
        {
            if (last_read_char == '\b')
            {
                putCh('\b');
                putCh(' ');
            }
            putCh(last_read_char);
        }

        unsigned char TIODriverBase::getCh()
        {
            last_read_char = _getCh();
            return last_read_char;
        }

        void TIODriverBase::putCh(const unsigned char &ch)
        {
            last_written_char = ch;
            _putCh(last_written_char);
        }

        void TIODriverBase::setVerbosing(bool active)
        {
            this->verbosing = active;
        }

        bool TIODriverBase::getVerbosing()
        {
            return this->verbosing;
        }

        void TIODriverBase::vpr(const char *str)
        {
            if (!verbosing)
                return;
            pr(str);
        }
        void TIODriverBase::vprln(const char *str)
        {
            if (!verbosing)
                return;
            prln(str);
        }
        void TIODriverBase::vputCh(const unsigned char &ch)
        {
            if (!verbosing)
                return;
            putCh(ch);
        }

        void TIODriverBase::setWarning(bool active)
        {
            this->warning = active;
        }
        bool TIODriverBase::getWarning()
        {
            return this->warning;
        }

        void TIODriverBase::wpr(const char *str)
        {
            if (!warning)
                return;
            pr(str);
        }
        void TIODriverBase::wprln(const char *str)
        {
            if (!warning)
                return;
            prln(str);
        }
        void TIODriverBase::wputCh(const unsigned char &ch)
        {
            if (!warning)
                return;
            putCh(ch);
        }

        const char *TIODriverBase::str(runnableStateT s)
        {
            switch (s)
            {
            case runnableStateT::inited:
                return "inited";
            case runnableStateT::paused:
                return "paused";
            case runnableStateT::running:
                return "running";
            case runnableStateT::scheduled:
                return "scheduled";
            case runnableStateT::terminated:
                return "terminated";
            case runnableStateT::scheduling:
                return "scheduling";
            default:
                return "none";
            }
        }

        const char *TIODriverBase::str(scheduleResultT s)
        {
            switch (s)
            {
            case scheduleResultT::scheduled:
                return "scheduled";
            case scheduleResultT::no_space:
                return "no_space";
            case scheduleResultT::no_core_submitted:
                return "no_core_submitted";
            case scheduleResultT::already_scheduled:
                return "already_scheduled";
            default:
                return "none";
            }
        }

        TIODriverBase *TIODriverBase::singleton;
    };
};