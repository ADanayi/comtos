// In the name of Allah

#ifndef __COMTOS_TERM_TYPES_H
#define __COMTOS_TERM_TYPES_H

namespace comtos
{
    namespace terminal
    {
        enum class TerminalStateT
        {
            idle = 0,
            getting_input = 1,
            joined_command = 2
        };

        enum class CommandReturnT
        {
            success = 0,
            error = 1
        };
    };
};

#endif