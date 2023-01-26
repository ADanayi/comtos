// In the name of Allah

// Decleration of all classes
namespace comtos
{
    class CoreBase;
    class Runnable;
    class Interval;
    class Finterval;
    class Timeout;
    namespace tools
    {
        class FlagTimeout;
        class EventFlagTimeout;
        class EventFlagRepeater;
        class AutoBooleanFlag;
        class ReverseWatchdog;
        class Clock;
        class RootInterval;
    };
    namespace terminal
    {
        class Terminal;
        class Command;
        class TIODriverBase; 
    };
}

// Including all class prototypes and class declerations
#include "settings.h"
#include "Core/types.h"
#include "Runnables/Runnable.h"
#include "Runnables/Timeout.h"
#include "Runnables/Interval.h"
#include "Core/CoreBase.h"
#include "Tools/Tools.h"
#include "Terminal/Terminal.h"
#include "Terminal/Commands/Commands.h"

// No source builds...
#ifndef _COMT_BUILD_USE_SOURCES
    #ifndef _COMT_BUILD_NO_SOURCES_TIC
    #define  _COMT_BUILD_NO_SOURCES_TIC
        #include "Core/CoreBase.cpp"
        
        #include "Runnables/Runnable.cpp"
        #include "Runnables/Timeout.cpp"
        #include "Runnables/Interval.cpp"

        #include "Tools/FlagTimeout.cpp"
        #include "Tools/EventFlagTimeout.cpp"
        #include "Tools/EventFlagRepeater.cpp"
        #include "Tools/AutoBooleanFlag.cpp"
        #include "Tools/ReverseWatchdog.cpp"
        #include "Tools/CircularFifo.cpp"

        #include "Terminal/TIODriverBase.cpp"
        #include "Terminal/Command.cpp"
        #include "Terminal/TerminalClass.cpp"

        #include "Terminal/Commands/Info.cpp"
        #include "Terminal/Commands/Verbose.cpp"
        #include "Terminal/Commands/Rbl.cpp"
    #endif
#endif
