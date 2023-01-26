// In the name of Allah

#ifndef COMTOS_TERM_COMMAND
#define COMTOS_TERM_COMMAND

#include "types.h"
#include "TIODriverBase.h"


namespace comtos
{
    namespace terminal
    {
        class Terminal;

        class __CommandHolder {
            friend class Terminal;
            public:
                __CommandHolder() {};
            private:
                __CommandHolder * prev;
                __CommandHolder * next;
        };

        class Command : private __CommandHolder
        {
            friend class Terminal;

        public:
            explicit Command(Command &) = delete;
            explicit Command();

            static bool compareCurrentArg(const char * argl, const char * val); // Compares current arg with val
            static const char * jumpToArg(const char * argl, const char * defaultEnd = nullptr);   // Skips to the beginning of the current arg. returns nullptr if no arg presented...
            static const char * fetchArgAndJump(char *argl, const char * defaultEnd = nullptr); // Terminates the beginning of the current arg and returns the pointer to next reduced argl. returns nullptr if no more args...

        protected:
            virtual const char *cname() = 0;
            virtual CommandReturnT run(const char *argl) = 0;
            virtual const char *help();

            TIODriverBase *io;
            Terminal * comterm;

        private:
            void __install(TIODriverBase * io, Terminal * term);
        };
    };
};

#endif
