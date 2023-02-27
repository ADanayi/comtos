// In the name of Allah

#include "../Cores/ESP32Comtos.h"

ESP32Comtos os;
void __root_setup();
void __root_loop();
comtos::tools::RootInterval root(__root_setup, __root_loop);

void setup()
{
    printf("Comtos is loading: ");
    os.boot(nullptr);
    __println("[Done]");

    printf("Scheduling root runnable: ");
    os.schedule_runnable(&root);
    return;
    __println("[Done]");

    __println("Setup completed");
}

void loop()
{
    os.join_loop();
    return;
}

#define setup __root_setup
#define loop __root_loop
