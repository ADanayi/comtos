// In the name of Allah

// In the name of Allah

#ifndef __ARD_COMTOS_H
#define __ARD_COMTOS_H

#include "Arduino.h"
#include "avr/wdt.h"
#include "../../comtos.h"

using namespace comtos;

void reset()
{
    wdt_disable();
    wdt_enable(WDTO_15MS);
    while (1)
    {
    }
}

class ArduinoAVRComtos : public CoreBase
{
public:
    ArduinoAVRComtos(ticT maxAllowedExecTime = 500) : CoreBase(maxAllowedExecTime){};

    virtual void boot(terminal::TIODriverBase *io = nullptr)
    {
        CoreBase::boot(io);
        wdt_disable();
    };

    ticT ctic() override
    {
        return ::millis();
    };

protected:
    void on_initializing() override
    {
#ifndef _COMT_COMPACT
        Serial.println("ArduinoAVRComtos >> on_initializing");
#endif
    };

    void on_singleton_changed() override final
    {
#ifndef _COMT_COMPACT
        Serial.println("ArduinoAVRComtos >> on_singleton_changed");
#endif
    }

#ifdef _COMT_WATCH_TIME_VIOLATIONS
    void on_max_allowed_exectime_violation(Runnable *violated, ticT pureExectime, ticT pollingtime) override final
    {
#ifndef _COMT_COMPACT
        Serial.print("ArduinoAVRComtos >> on_max_allowed_exectime_violation @ ");
        Serial.println(violated->runame());
        Serial.print("pure exec time: ");
        Serial.println(pureExectime);
        Serial.print("polling time: ");
        Serial.println(pollingtime);

        Serial.println("Restarting...");
#endif
        reset();
    }
#endif

    void on_error(errorT E) override final
    {
#ifndef _COMT_COMPACT
        Serial.println("ArduinoAVRComtos >> on_error");
        switch (E)
        {
#ifdef _COMT_WATCH_TIME_VIOLATIONS
        case errorT::polling_loop:
            Serial.println("Polling loop?!");
            break;
        case errorT::wrong_polling_finisher:
            Serial.println("wrong_polling_finisher");
            Serial.print("polling on: ");
            Serial.println(__polling_runnable->runame());
            Serial.print("polling requester: ");
            Serial.println(__polling_func_requester->runame());
            break;
        case errorT::unfinished_polling:
            Serial.println("unfinished_polling");
            break;
        case errorT::wrong_polling_requester:
            Serial.println("wrong_polling_requester");
            break;
#endif
        case errorT::core_is_null:
            Serial.println("core is null?!");
            break;
        case errorT::no_space_on_core:
            Serial.println("no more space on core?!");
            break;
        default:
            Serial.println("Unknown error!");
        }
        delay(20000);
#endif
        reset();
    }

    void on_warning(warningT w) override
    {
#ifndef _COMT_COMPACT
        Serial.print("ArduinoAVRComtos >> warning: ");
        switch (w)
        {
        case warningT::unfinished_polling:
            Serial.println("unfinished_polling");
            break;

        default:
            Serial.println("unknown");
            break;
        }
#endif
    }

    virtual void on_main_loop_started()
    {
#ifndef _COMT_COMPACT
        Serial.println("ArduinoAVRComtos >> on_main_loop_started");
#endif
    }

    virtual void on_main_loop_finished()
    {
#ifndef _COMT_COMPACT
        Serial.println("ArduinoAVRComtos >> on_main_loop_finished");
        Serial.print("This should not happen -> restart");
#endif
        reset();
    }

    virtual void on_loop_iterated()
    {
    }

    virtual void on_schedule_request(Runnable *R)
    {
        // Serial.println("ArduinoAVRComtos >> on_schedule_request");
    }

    virtual void on_schedule_request_accepted(Runnable *R)
    {
        // Serial.println("ArduinoAVRComtos >> on_schedule_request_accepted");
    }
};

#endif
