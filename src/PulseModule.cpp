#include <Arduino.h>

#define PULSE_PIN 15
#define MAX_RPM_CONSTANT 3662  // aproximadamente o limite de 8192RPM, também para debounce
#define TIME_DIVISION_CONSTANT 30000000

class PulseModule {
   private:
    volatile uint64_t lastPulsedMicros;
    volatile int rpm;
    volatile bool pulseHandled;

   public:
    PulseModule() {
        this->rpm = 0;
        this->lastPulsedMicros = 0;
        this->pulseHandled = true;
        pinMode(PULSE_PIN, INPUT_PULLDOWN);
    }

    void handlePulseInterrupt() {
        uint64_t now = micros();
        uint64_t difference = now - lastPulsedMicros;
        if (difference > MAX_RPM_CONSTANT) {
            this->rpm = (int)TIME_DIVISION_CONSTANT / difference;
            this->lastPulsedMicros = now;
            this->pulseHandled = false;
        }
    }

    void handleRpm() {
        uint64_t now = micros();
        if (now >= this->lastPulsedMicros + 1000000) {
            this->rpm = 0;
        }
    }

    int getRpm() {
        return this->rpm;
    }

    bool isPulseHandled() {
        return this->pulseHandled;
    }

    void resetPulsseHandled() {
        this->pulseHandled = true;
    }
};