#include <Arduino.h>
#include "PupitrePSTJ.h"


PupitrePSTJ pupitre = PupitrePSTJ(
        6, 7, 8, 9, 10, 11, // Leds
        3, 4, 5, 2, // Ligne
        13, 12, // Fire & clef
        A3, // btns
        A6, A7, // Encodeur
        A4, A5, 0x27 // LCD
);

uint32_t loopMinTime = 3;

void setup() {
    Serial.begin(115200);
    pupitre.init();
}

void loop() {
    uint32_t startTime = millis();

    pupitre.update();

    uint32_t endTime = millis();
    if (endTime - startTime < loopMinTime) {
        delay(loopMinTime + startTime - endTime);

//        Serial.println(digitalRead(13));
    }

}
