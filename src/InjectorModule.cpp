#include <Arduino.h>
#include <EEPROM.h>

#include <interval.cpp>
#include <timeout.cpp>

#define INJECTOR_PIN 2

class InjectorModule {
   private:
    Timeout *injectorTimeout;
    static void setInjectorPinOn() {
        digitalWrite(INJECTOR_PIN, HIGH);
    }
    static void setInjectorPinOff() {
        digitalWrite(INJECTOR_PIN, LOW);
    }

   public:
    InjectorModule() {
        pinMode(INJECTOR_PIN, OUTPUT);
        int injectionTime = 12;  // EPROM.read(0);
        Serial.println(injectionTime);
        this->injectorTimeout = new Timeout(injectionTime * 1000, setInjectorPinOff, setInjectorPinOn, micros);
    }

    void tick() {
        this->injectorTimeout->tick();
    }

    void startInjector() {
        this->injectorTimeout->start();
    }

    void updateInjectionTime(int newInjectionTime) {
        if (newInjectionTime >= 0 && newInjectionTime <= 255) {
            EEPROM.write(0, newInjectionTime);
            this->injectorTimeout->setTimeout(newInjectionTime);
        }
    }

    unsigned long getTimeout() {
        return this->injectorTimeout->getTimeout();
    }
};