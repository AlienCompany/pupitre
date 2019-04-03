#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
//
// Created by hugue on 02/04/2019.
//

#include "MultiplexLed.h"

MultiplexLed::MultiplexLed(
        const ArrayFix<const byte> &pinsLeds,
        const ArrayFix<const byte> &pinColors,
        const MultiplexMode multiplexMode)
        : PINS_LEDS(pinsLeds),
          PINS_COLORS(pinColors),
          multiplexMode(multiplexMode),
          colors(pinsLeds.length * pinColors.length) {
}

void MultiplexLed::setBrightness(uint8_t ledIndex, uint8_t colorIndex, uint8_t value) {
    setBrightness(indexOf(ledIndex, colorIndex), value);
}

uint8_t MultiplexLed::indexOf(uint8_t ledIndex, uint8_t colorIndex) {
    return ledIndex * PINS_COLORS.length + colorIndex;
}

void MultiplexLed::setBrightness(uint8_t ledIndex, uint8_t brightness) {
    colors.array[ledIndex] = brightness;
}

void MultiplexLed::setColor(uint8_t group, Color color) {
    setBrightness(group, 0, color.r);
    setBrightness(group, 1, color.g);
    setBrightness(group, 2, color.b);
}

void MultiplexLed::setColor(uint8_t group, uint32_t color) {
    setColor(group,Color(color));
}

uint8_t MultiplexLed::getBrightness(uint8_t ledIndex, uint8_t colorIndex) {
    return colors.array[indexOf(ledIndex, colorIndex)];
}

Color MultiplexLed::getColor(uint8_t ledIndex) {
    return Color(getBrightness(ledIndex, 0), getBrightness(ledIndex, 1), getBrightness(ledIndex, 2));
}

void MultiplexLed::changeCurrentLed() {

    uint8_t ledEnableValue = LOW;
    uint8_t ledDisableValue = HIGH;
    if (multiplexMode == ANODE_GROUP) {
        ledEnableValue = HIGH;
        ledDisableValue = LOW;
    }

    digitalWrite(PINS_LEDS.array[currentLedIndex], ledDisableValue);
    currentLedIndex++;
    if (currentLedIndex == PINS_LEDS.length) currentLedIndex = 0;
    for (uint8_t i = 0; i < PINS_COLORS.length; i++) {
        uint8_t value = getBrightness(currentLedIndex, 0);
        if (multiplexMode == ANODE_GROUP) value ^= 255;

        if(value == 0){
            digitalWrite(PINS_COLORS.array[i], LOW);
        } else if(value == 255){
            digitalWrite(PINS_COLORS.array[i], HIGH);
        } else{
            analogWrite(PINS_COLORS.array[i], value);
        }
    }

    digitalWrite(PINS_LEDS.array[currentLedIndex], ledEnableValue);
}

void MultiplexLed::update() {
    if (nextUpadate > millis()) {
        changeCurrentLed();
        nextUpadate = millis() + periode;
    }
}

void MultiplexLed::init() {

    uint8_t ledDisableValue = HIGH;
    if (multiplexMode == ANODE_GROUP) {
        ledDisableValue = LOW;
    }

    for(uint8_t i = 0 ; i < PINS_LEDS.length; i++){
        pinMode(PINS_LEDS.array[i], ledDisableValue);
    }
    for(uint8_t i = 0 ; i < PINS_COLORS.length; i++)
        pinMode(PINS_COLORS.array[i], OUTPUT);

}

#pragma clang diagnostic pop