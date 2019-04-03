//
// Created by ferna on 08/11/2018.
//

#ifndef REVEIL_LCD_H
#define REVEIL_LCD_H

#include <IPAddress.h>
#include "LiquidCrystal_I2C.h"

class Lcd {
private:
    LiquidCrystal_I2C *lcdI2C;

    int seconds = 00;
    int minutes = 00;
    int hours = 00;


public:
    Lcd(uint8_t address, uint8_t column, uint8_t row);

    void init();

    void hour();

    void printHour();

    void progressbar(uint8_t c, uint8_t l, uint8_t size, float value);

    ~Lcd();

    void printIp(IPAddress address);

    void printWiFiFirmwareVersion(char *string);

    void clear();

    void loading(const char *msg, float progressBar);

    void loading(const char *msg1, const char *msg2, float progressBar);

    void printCentre(int line, const char *msg);
};


#endif //REVEIL_LCD_H
