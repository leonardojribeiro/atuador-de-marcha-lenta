#include <Arduino.h>

#include <interval.cpp>
#include <timeout.cpp>

#define PUMP_PIN 4

class PumpModule {
   private:
    Timeout *pumpTimeout;
    static void setPumpPinOn() {
        digitalWrite(PUMP_PIN, HIGH);
    }
    static void setPumpPinOff() {
        digitalWrite(PUMP_PIN, LOW);
    }

   public:
    PumpModule() {
        pinMode(PUMP_PIN, OUTPUT);
        this->pumpTimeout = new Timeout(1000000, setPumpPinOff, setPumpPinOn, micros);
    }

    void tick() {
        this->pumpTimeout->tick();
    }

    void startPump() {
        this->pumpTimeout->start();
    }
};