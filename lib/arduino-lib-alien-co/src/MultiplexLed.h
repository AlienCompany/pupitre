#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
//
// Created by hugue on 02/04/2019.
//

#ifndef PUPITRE_MULTIPLEXLED_H
#define PUPITRE_MULTIPLEXLED_H

#include <Arduino.h>
#include "ArrayFix.h"

enum MultiplexMode {
    ANODE_GROUP,
    CATODE_GROUP
};

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    explicit Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

    explicit Color(uint32_t value = 0) : r(value >> 16), g(value >> 8), b(value) {}

    uint32_t value() const {
        return ((((uint32_t) r) << (uint32_t) 16) & 0xFF0000) + ((g << 8) & 0x00FF00) + (b & 0x0000FF);
    }
    static Color COLOR_ORANGE() {return Color(0xef6c00); }
    static Color COLOR_WHITE(){ return Color(0xFFFFFF); }
    static Color COLOR_RED(){ return Color(0xFF0000); }
    static Color COLOR_GREEN(){ return Color(0x00FF00); }
    static Color COLOR_BLUE(){ return Color(0x0000FF); }
    static Color COLOR_PURPULE(){ return Color(0x8e24aa); }
    static Color COLOR_BLACK(){ return Color(0); }
};
class MultiplexLed {
private:
    const ArrayFix<byte> colors;
    const ArrayFix<const byte> PINS_LEDS;
    const ArrayFix<const byte> PINS_COLORS;
    MultiplexMode multiplexMode;
    uint32_t nextUpadate = 0;
    uint32_t periode = 3;
    uint8_t currentLedIndex = 0;

public:

    MultiplexLed(const ArrayFix<const byte> &pinsLeds, const ArrayFix<const byte> &pinColors,
                 MultiplexMode multiplexMode = ANODE_GROUP);

    uint8_t indexOf(uint8_t ledIndex, uint8_t colorIndex);

    void setBrightness(uint8_t ledIndex, uint8_t colorIndex, uint8_t value);

    void setBrightness(uint8_t ledIndex, uint8_t brightness);


    void setColor(uint8_t group, Color color);

    void setColor(uint8_t group, uint32_t color);

    uint8_t getBrightness(uint8_t ledIndex, uint8_t colorIndex);

    Color getColor(uint8_t ledIndex);

    void changeCurrentLed();

    void update();

    void init();
};


#endif //PUPITRE_MULTIPLEXLED_H

#pragma clang diagnostic pop