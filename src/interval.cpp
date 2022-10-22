#include <Arduino.h>
#ifndef Interval_t
#define Interval_t
class Interval {
   private:
    unsigned long time = 0;
    unsigned int interval;
    void (*callback)();
    unsigned long (*getTimer)();

   public:
    Interval(unsigned int interval, void (*callback)(), unsigned long (*getTimer)()) {
        this->interval = interval;
        this->callback = callback;
        this->getTimer = getTimer;
    }

    void setinterval(unsigned int interval) {
        this->interval = interval;
    }

    void tick() {
        if (this->getTimer() >= this->time + this->interval) {
            this->callback();
            this->time = this->getTimer();
        }
    }
};
#endif