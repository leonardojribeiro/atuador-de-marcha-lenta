#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

class DisplayModule {
   public:
    Adafruit_SSD1306 *display;
    DisplayModule() {
        display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
        if (!display->begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
            Serial.println(F("SSD1306 allocation failed"));
            for (;;)
                ;  // Don't proceed, loop forever
        } 
        display->setRotation(2);
        display->display();
        display->setTextColor(WHITE);
    }
    void setRpm(int rpm) {
        display->clearDisplay();
        display->setTextSize(2);
        display->setCursor(0, 0);
        display->printf("RPM: %d\n", rpm);
    }
};