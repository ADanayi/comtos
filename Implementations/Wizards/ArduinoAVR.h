// In the name of Allah

#include "../Cores/ArduinoAVRComtos.h"

ArduinoAVRComtos os;
void __root_setup();
void __root_loop();
comtos::tools::RootInterval root(__root_setup, __root_loop);

void setup()
{
    Serial.begin(115200);
    Serial.print("Comtos is loading: ");
    os.boot();
    Serial.println("[Done]");

    Serial.print("Scheduling root runnable: ");
    os.schedule_runnable(&root);
    Serial.println("[Done]");

    Serial.println("Setup completed");
}

void loop()
{
    os.join_loop();
}

#define setup __root_setup
#define loop __root_loop
