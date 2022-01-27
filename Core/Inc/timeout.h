#include <stdbool.h>

typedef struct Timeout {
	unsigned long int *time;
	unsigned long int timeout;
	unsigned long int lastTime;
	bool timedOut;
	void (*onTimeout)();
	void (*onReset)();
	void (*handleTimeout)(struct Timeout *timeout);
	void (*resetTimeout)(struct Timeout *timeout);
} Timeout;


void handleTimeout(struct Timeout *timeout);

void resetTimeout(struct Timeout *timeout);

void initializeTimeout(Timeout * timeout, unsigned long int *time, unsigned long int timeoutTime, void (*onTimeout)(), void(*onReset)());


