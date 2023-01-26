// In the name of Allah

#ifndef __ARD_COMTOS_H
#define __ARD_COMTOS_H

#include "Arduino.h"
#include "../../comtos.h"
#include "Esp.h"

#ifndef DEBUG_no_watchdog
#include <esp_task_wdt.h>
#endif

using namespace comtos;

class ArduinoESP32Comtos : public CoreBase
{
public:
    ArduinoESP32Comtos() : CoreBase(500)
    {
        __use_wdt = false;
    };

    virtual void boot(bool use_wdt, terminal::TIODriverBase *io = nullptr)
    {
        CoreBase::boot(io);
        __use_wdt = use_wdt;
    };

protected:
    bool __use_wdt;

    ticT ctic() override
    {
        return ::millis();
    };

    void on_initializing() override
    {
        Serial.println("ArduinoESP32Comtos >> on_initializing");
    };

    void on_singleton_changed() override final
    {
        Serial.println("ArduinoESP32Comtos >> on_singleton_changed");
    }

#ifdef _COMT_WATCH_TIME_VIOLATIONS
    void on_max_allowed_exectime_violation(Runnable *violated, ticT pureExectime, ticT pollingtime) override final
    {
        Serial.print("ArduinoESP32Comtos >> on_max_allowed_exectime_violation @ ");
        Serial.println(violated->runame());
        Serial.print("pure exec time: ");
        Serial.println(pureExectime);
        Serial.print("polling time: ");
        Serial.println(pollingtime);

        Serial.println("Restarting...");
        ESP.restart();
    }
#endif

    void on_error(errorT E) override final
    {
        Serial.println("ArduinoESP32Comtos >> on_error");
        switch (E)
        {
        case errorT::polling_loop:
            Serial.println("Polling loop?!");
            break;
        case errorT::wrong_polling_finisher:
            Serial.println("wrong_polling_finisher");
            Serial.print("polling on: ");
            Serial.println(__polling_runnable->runame());
            Serial.print("polling requester: ");
            Serial.println(__polling_runnable->runame());
            break;
        case errorT::unfinished_polling:
            Serial.println("unfinished_polling");
            break;
        case errorT::core_is_null:
            Serial.println("core is null?!");
            break;
        case errorT::no_space_on_core:
            Serial.println("no more space on core?!");
            break;
        case errorT::wrong_polling_requester:
            Serial.println("wrong_polling_requester");
            break;
        default:
            Serial.println("Unknown error!");
        }
        delay(20000);
        ESP.restart();
    }

    void on_warning(warningT w) override
    {
        Serial.print("ArduinoESP32Comtos >> warning: ");
        switch (w)
        {
        case warningT::unfinished_polling:
            Serial.println("unfinished_polling");
            break;

        default:
            Serial.println("unknown");
            break;
        }
    }

    virtual void on_main_loop_started()
    {
        Serial.println("ArduinoESP32Comtos >> on_main_loop_started");
        if (__use_wdt)
        {
            Serial.print("\tInitializing Watchdog >> ");
            esp_task_wdt_init(20, true);
            esp_task_wdt_add(NULL); // add current thread to WDT watch
            Serial.print("set on ");
            Serial.print(20);
            Serial.println("seconds.");
        }
    }

    virtual void on_main_loop_finished()
    {
        Serial.println("ArduinoESP32Comtos >> on_main_loop_finished");
        Serial.print("This should not happen -> restart");
        ESP.restart();
    }

    virtual void on_loop_iterated()
    {
        if (__use_wdt)
        {
            esp_task_wdt_reset();
        }
        else
        {
        }
        delay(1);
    }

    virtual void on_schedule_request(Runnable *R)
    {
        Serial.printf("ArduinoESP32Comtos >> on_schedule_request for %s\n", R->runame());
    }

    virtual void on_schedule_request_accepted(Runnable *R)
    {
        Serial.printf("ArduinoESP32Comtos >> on_schedule_request_accepted for %s\n", R->runame());
    }
};

#endif
