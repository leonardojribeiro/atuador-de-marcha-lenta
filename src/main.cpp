
#include <Arduino.h>
#include <SPI.h>

#include <DisplayModule.cpp>
#include <InjectorModule.cpp>
#include <PulseModule.cpp>
#include <PumpModule.cpp>
#include <interval.cpp>

PumpModule *pumpModule;
InjectorModule *injectorModule;
PulseModule *pulseModule;
DisplayModule *displayModule;

Interval *verificationRpmInterval;
Interval *updateDisplayInterval;
Interval *updateRpmInterval;

void handleTimeInterrupt() {
    injectorModule->tick();
    pumpModule->tick();
}

void verifyRpm() {
    int rpm = pulseModule->getRpm();
    bool isStarting = rpm < 450;
    bool isRunning = rpm > 0;
    bool canStartPump = rpm < 1000;
    bool canStartInjector = rpm < 800 && !pulseModule->isPulseHandled();
    if (isRunning) {
        if (isStarting) {
            verificationRpmInterval->setinterval(500);
        } else {
            verificationRpmInterval->setinterval(250);
        }
        if (canStartPump) {
            pumpModule->startPump();
            if (canStartInjector) {
                injectorModule->startInjector();
                pulseModule->resetPulsseHandled();
            }
        }
    }
}

void setupTimer() {
    hw_timer_t *timer = timerBegin(0, 8000, true);
    timerAttachInterrupt(timer, handleTimeInterrupt, true);
    timerAlarmWrite(timer, 5, true);
    timerAlarmEnable(timer);
}

void handlePulseInterrupt() {
    pulseModule->handlePulseInterrupt();
}

void handleUpdateDisplay() {
    displayModule->setRpm(pulseModule->getRpm());
    displayModule->display->display();
}

void handleUpdateRpm() {
    pulseModule->handleRpm();
}

void setup() {
    Serial.begin(115200);
    pumpModule = new PumpModule();
    injectorModule = new InjectorModule();
    pulseModule = new PulseModule();
    attachInterrupt(PULSE_PIN, handlePulseInterrupt, FALLING);
    verificationRpmInterval = new Interval(250, verifyRpm, millis);
    displayModule = new DisplayModule();
    updateDisplayInterval = new Interval(100, handleUpdateDisplay, millis);
    updateRpmInterval = new Interval(1000, handleUpdateRpm, millis);
    setupTimer();
}

void loop() {
    updateRpmInterval->tick();
    verificationRpmInterval->tick();
    updateDisplayInterval->tick();
}
