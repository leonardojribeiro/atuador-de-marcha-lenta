#include "timeout.h"

void handleTimeout(struct Timeout *timeout) {
	if (*timeout->time >= timeout->lastTime + timeout->timeout && !timeout->timedOut) {
		timeout->onTimeout();
		timeout->timedOut = true;
		timeout->lastTime = *timeout->time;
	}
}

void resetTimeout(struct Timeout *timeout){
	timeout->onReset();
	timeout->lastTime = *timeout->time;
	timeout->timedOut = false;
}

void initializeTimeout(Timeout * timeout, unsigned long int *time, unsigned long int timeoutTime, void (*onTimeout)(), void(*onReset)()) {
	*timeout = (Timeout ) { time, timeoutTime, 0, true, onTimeout, onReset, handleTimeout, resetTimeout };
}
