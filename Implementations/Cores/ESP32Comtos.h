// In the name of Allah

// In the name of Allah

#ifndef __IDF_ESP32_COMTOS_H
#define __IDF_ESP32_COMTOS_H

#include "../../comtos.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_task_wdt.h"

using namespace comtos;

void reset()
{
    esp_restart();
}

unsigned long millis()
{
    return (unsigned long)(esp_timer_get_time() / 1000ULL);
}

void delay(uint32_t ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

void __println(const char *str)
{
    printf(str);
    printf("\n");
}


void __tic_wdt()
{
    vTaskDelay(1);
}

class ESP32Comtos : public CoreBase
{
public:
    ESP32Comtos(ticT maxAllowedExecTime = 500) : CoreBase(maxAllowedExecTime){};

    virtual void boot(terminal::TIODriverBase *io = nullptr)
    {
        CoreBase::boot(io);
    };

    ticT ctic() override
    {
        return ::millis();
    };

protected:
    void on_initializing() override
    {
#ifndef _COMT_COMPACT
        printf("ESP32Comtos >> on_initializing\n");
#endif
    };

    void on_singleton_changed() override final
    {
#ifndef _COMT_COMPACT
        printf("ESP32Comtos >> on_singleton_changed\n");
#endif
    }

#ifdef _COMT_WATCH_TIME_VIOLATIONS
    void on_max_allowed_exectime_violation(Runnable *violated, ticT pureExectime, ticT pollingtime) override final
    {
#ifndef _COMT_COMPACT
        printf("ESP32Comtos >> on_max_allowed_exectime_violation @ ");
        __println(violated->runame());
        printf("pure exec time: ");
        __println(pureExectime);
        printf("polling time: ");
        __println(pollingtime);

        __println("Restarting...");
#endif
        reset();
    }
#endif

    void on_error(errorT E) override final
    {
#ifndef _COMT_COMPACT
        printf("ESP32Comtos >> on_error\n");
        switch (E)
        {
#ifdef _COMT_WATCH_TIME_VIOLATIONS
        case errorT::polling_loop:
            printf("Polling loop?!\n");
            break;
        case errorT::wrong_polling_finisher:
            printf("wrong_polling_finisher\n");
            printf("polling on: ");
            __println(__polling_runnable->runame());
            printf("polling requester: ");
            __println(__polling_func_requester->runame());
            break;
        case errorT::unfinished_polling:
            __println("unfinished_polling");
            break;
        case errorT::wrong_polling_requester:
            __println("wrong_polling_requester");
            break;
#endif
        case errorT::core_is_null:
            __println("core is null?!");
            break;
        case errorT::no_space_on_core:
            __println("no more space on core?!");
            break;
        default:
            __println("Unknown error!");
        }
        delay(20000);
#endif
        reset();
    }

    void on_warning(warningT w) override
    {
#ifndef _COMT_COMPACT
        printf("ESP32Comtos >> warning: ");
        switch (w)
        {
        case warningT::unfinished_polling:
            __println("unfinished_polling");
            break;

        default:
            __println("unknown");
            break;
        }
#endif
    }

    virtual void on_main_loop_started()
    {
#ifndef _COMT_COMPACT
        __println("ESP32Comtos >> on_main_loop_started");
#endif
    }

    virtual void on_main_loop_finished()
    {
#ifndef _COMT_COMPACT
        __println("ESP32Comtos >> on_main_loop_finished");
        printf("This should not happen -> restart");
#endif
        reset();
    }

    virtual void on_loop_iterated()
    {
        __tic_wdt();
    }

    virtual void on_cursor_iterated()
    {
        __tic_wdt();
    }

    virtual void on_schedule_request(Runnable *R)
    {
#ifndef _COMT_COMPACT
        printf("ESP32Comtos >> on_schedule_request for %s\n", R->runame());
#endif
    }

    virtual void on_schedule_request_accepted(Runnable *R)
    {
#ifndef _COMT_COMPACT
        printf("ESP32Comtos >> on_schedule_request_accepted for %s\n", R->runame());
#endif
    }
};

#endif
