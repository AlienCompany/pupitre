//
// Created by ferna on 05/09/2018.
//

#ifndef LETTER_BOX_LED_H
#define LETTER_BOX_LED_H


#include <Arduino.h>

class Led {
private:

    uint8_t PIN_LED;


    byte brightness; // 0 to 255

public:

    Led(uint8_t PIN_LED);

    Led(uint8_t PIN_LED, int brightness);

    void init();

    byte getBrightness() const;

    void setBrightness(byte brightness);

    void on() { setBrightness(255); }

    void off() { setBrightness(0); }

    void switchTo(boolean value) { setBrightness(value * 255); }

    virtual ~Led();
};


#endif //LETTER_BOX_LED_H
