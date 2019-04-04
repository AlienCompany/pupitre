#include <Arduino.h>
#include "PupitrePSTJ.h"


PupitrePSTJ pupitre = PupitrePSTJ(
        6, 7, 8, 9, 10, 11, // Leds
        5, 4, 3, 2, // Ligne
        13, 12, // Fire & clef
        A0, // btns
        A1, A2, // Encodeur
        A4, A5 // LCD
);

uint32_t loopMinTime = 3;

void setup() {
    // Serial.begin(9600);
    pupitre.init();
}

void loop() {
    uint32_t startTime = millis();

    pupitre.update();

    uint32_t endTime = millis();
    if (endTime - startTime < loopMinTime) {
        delay(loopMinTime + startTime - endTime);
    }

}
