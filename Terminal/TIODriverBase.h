// In the name of Allah

#ifndef __COMTOS_TIO_H
#define __COMTOS_TIO_H

#include "../Core/types.h"

namespace comtos
{
    namespace terminal
    {
        class TIODriverBase
        {
            //////////////////////////////////////////////////////
        public:
            virtual bool hasCh() = 0;

        protected:
            virtual unsigned char _getCh() = 0;
            virtual void _putCh(const unsigned char &ch) = 0;
            //////////////////////////////////////////////////////

        public:
            static TIODriverBase *singleton;

            explicit TIODriverBase(TIODriverBase &) = delete;
            explicit TIODriverBase();

            void pr(const char *str);
            void prln(const char *str);

            void vpr(const char *str);
            void vprln(const char *str);
            void vputCh(const unsigned char &ch);

            void wpr(const char *str);
            void wprln(const char *str);
            void wputCh(const unsigned char &ch);

            unsigned char getCh();
            void putCh(const unsigned char &ch);
            virtual void newline();
            virtual void echo_last_char();

            void setVerbosing(bool active);
            void setWarning(bool active);
            bool getVerbosing();
            bool getWarning();

            static const char * str(runnableStateT s);
            static const char * str(scheduleResultT s);

        private:
            unsigned char last_read_char;
            unsigned char last_written_char;

            friend class Terminal;

            bool verbosing;
            bool warning;
        };
    };
};

#endif
