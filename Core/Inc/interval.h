
typedef struct Interval {
	unsigned long int *time;
	unsigned long int interval;
	unsigned long int lastTime;
	void (*callback)();
	void (*handle)(struct Interval *interval);
} Interval;


void handle(struct Interval *interval);


void initializeInterval(Interval * interval, unsigned long int *time, unsigned long int intervalTime, void (*callback)());
