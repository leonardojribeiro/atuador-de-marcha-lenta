#include <Arduino.h>
#ifndef Timeout_t

#define Timeout_t
class Timeout {
   private:
    unsigned long time = 0;
    unsigned long timeout;
    void (*onTimeout)();
    void (*onStart)();
    bool timedOut = true;
    unsigned long (*getTimer)();

   public:
    Timeout(unsigned long timeout, void (*onTimeout)(), void (*onStart)(), unsigned long (*getTimer)()) {
        this->timeout = timeout;
        this->onTimeout = onTimeout;
        this->onStart = onStart;
        this->getTimer = getTimer;
    }

    void setTimeout(unsigned int timeout) {
        this->timeout = timeout;
    }

    unsigned long getTimeout() {
        return this->timeout;
    }

    void tick() {
        if (this->getTimer() >= (this->time + this->timeout) && !this->timedOut) { 
            this->onTimeout();
            this->timedOut = true;
        }
    }

    void start() {
        this->onStart();
        this->time = this->getTimer();
        this->timedOut = false; 
    }
};
#endif