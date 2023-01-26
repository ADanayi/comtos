// In the name of Allah

#include "../../settings.h"

#if defined(_COMT_BUILD_USE_SOURCES)
#undef _COMT_BUILD_USE_SOURCES
#endif

#include <Arduino.h>

#if defined(__AVR__)
#include "./ArduinoAVR.h"
#elif defined(ESP32)
#include "./ArduinoESP32.h"
#endif
