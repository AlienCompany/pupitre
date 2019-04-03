//
// Created by ferna on 05/09/2018.
//

#include "Led.h"

Led::Led(uint8_t PIN_LED) : PIN_LED(PIN_LED) {}

Led::Led(uint8_t PIN_LED, int brightness) : PIN_LED(PIN_LED), brightness(brightness) {}

void Led::init() {
    pinMode(PIN_LED, OUTPUT);
    analogWrite(PIN_LED, brightness);
}

byte Led::getBrightness() const {
    return brightness;
}

void Led::setBrightness(byte brightness) {
    Led::brightness = brightness;
    if(brightness == 255 || brightness == 0){
        digitalWrite(PIN_LED, brightness == 255);
    }else{
        analogWrite(PIN_LED, brightness);
    }
}

Led::~Led() {}
