#include "interval.h"

void handle(struct Interval *interval) {
	if (*interval->time >= interval->lastTime + interval->interval) {
		interval->callback();
		interval->lastTime = *interval->time;
	}
}

void initializeInterval(Interval * interval, unsigned long int *time, unsigned long int intervalTime, void (*callback)()) {
	*interval = (Interval ) { time, intervalTime, 0, callback, handle };
}
