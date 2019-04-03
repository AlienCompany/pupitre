//
// Created by ferna on 08/11/2018.
//
#include <LiquidCrystal_I2C.h>
#include "Lcd.h"


void Lcd::init() {

    lcdI2C->begin();
    lcdI2C->backlight();
    lcdI2C->home();
    lcdI2C->clear();

}

Lcd::Lcd(uint8_t address, uint8_t column, uint8_t row) {
    lcdI2C = new LiquidCrystal_I2C(address, column, row);
}

Lcd::~Lcd() = default;


void Lcd::printHour() {

    lcdI2C->setCursor(0, 0);

    if (hours < 10) {
        lcdI2C->print('0');
    }
    lcdI2C->print(hours);
    lcdI2C->print(":");
    if (minutes < 10) {
        lcdI2C->print('0');
    }
    lcdI2C->print(minutes);
    lcdI2C->print(":");
    if (seconds < 10) {
        lcdI2C->print('0');
    }
    lcdI2C->print(seconds);


}

void Lcd::hour() {

    if (seconds < 59) {
        seconds += 1;
    } else {
        seconds = 00;
        if (minutes < 59) {
            minutes += 1;
        } else {
            minutes = 00;
            if (hours < 23) {
                hours += 1;
            } else {
                hours = 00;
            }
        }
    }

}

void Lcd::printIp(IPAddress address) {
    lcdI2C->setCursor(0,3);
    address.printTo(*lcdI2C);
}

void Lcd::printWiFiFirmwareVersion(char *string) {
    lcdI2C->setCursor(20-strlen(string),3);
    lcdI2C->print(string);

}

void Lcd::progressbar(uint8_t c, uint8_t l, uint8_t size, float value) {
    lcdI2C->setCursor(c,l);
    uint8_t nbActiveCell = value*size;
    int i;
    for(i=0; i<nbActiveCell;i++)
        lcdI2C->write(0xff);
    for(; i<size;i++)
        lcdI2C->write(0x5f);
}

void Lcd::clear() {
    lcdI2C->clear();
}

void Lcd::loading(const char *msg, float progressBar) {
    loading(msg,"",progressBar);
}
void Lcd::loading(const char *msg1, const char *msg2, float progressBar) {
    lcdI2C->clear();
    progressbar(5,1,10,progressBar);
    printCentre(2, msg1);
    printCentre(3, msg2);
}

void Lcd::printCentre(int line, const char *msg) {
    size_t msgLength = strlen(msg);
    lcdI2C->setCursor(10 - msgLength/2, line);
    lcdI2C->print(msg);
}
