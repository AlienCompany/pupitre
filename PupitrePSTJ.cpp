//
// Created by hugue on 04/04/2019.
//

#include "PupitrePSTJ.h"

PupitrePSTJ::PupitrePSTJ(byte pinLed1, byte pinLed2, byte pinLed3, byte pinLedColor1, byte pinLedColor2,
                         byte pinLedColor3, byte pinLine1, byte pinLine2, byte pinLine3, byte pinLineCom, byte pinFire,
                         byte pinClef, byte pinBtns, byte pinEncoderA, byte pinEncoderB, byte pinLcdSda, byte pinLcdScl,
                         byte lcdAddress)
        : PupitreBase(pinLed1, pinLed2, pinLed3, pinLedColor1, pinLedColor2, pinLedColor3, pinLine1, pinLine2, pinLine3,
                      pinLineCom, pinFire, pinClef, pinBtns, pinEncoderA, pinEncoderB, pinLcdSda, pinLcdScl) {
    lcdI2C = (new LiquidCrystal_I2C(lcdAddress, 20, 4));
}

void PupitrePSTJ::onKeyRemove() {
    Serial.println("onKeyRemove");
    setMode(MODE_SCANING);
    updateLedColor();
}

void PupitrePSTJ::onKeyInsert() {
    Serial.println("onKeyInsert");
    setMode(MODE_FIRE);
    updateLedColor();
}

void PupitrePSTJ::onClickFireWithoutKey() {
    Serial.println("onClickFireWithoutKey");
    for (uint8_t i = 0; i < 3; i++) {
        if (lineIsActive(i))leds.setColor(i, Color::COLOR_PURPULE());
    }
}

void PupitrePSTJ::onClickFireWithKey() {
    Serial.println("onClickFireWithKey");
    if (fire()) {
        fireStartTime = millis();
        fireEndTime = fireStartTime + fireDuration;
        updateLedColor();
    } else {
        danger();
    }
}

void PupitrePSTJ::danger() {
    displayDangerCount = 12;
    displayDangerNextChange = millis();
    updateLedColor();
}

void PupitrePSTJ::updateLedColor() {
    if (displayDangerCount) {
        if (displayDangerNextChange > millis()) return;
        displayDangerCount--;
        if (displayDangerCount) {
            displayDangerNextChange += 200;
            Color c = displayDangerCount & (uint32_t) 1 ? Color::COLOR_BLACK() : Color::COLOR_RED();
            leds.setColor(0, c);
            leds.setColor(1, c);
            leds.setColor(2, c);
            return;
        }
    }

    for (uint8_t line = 0; line < 3; line++) {
        Color c;
        if (isFired(line)) {
            c = Color::COLOR_RED();
        } else if (!lineIsActive(line)) {
            c = Color::COLOR_BLACK();
        } else if (getLineStat(line) == DISCONNECTED) {
            c = Color::COLOR_ORANGE();
        } else if (getLineStat(line) == CONNECTED) {
            c = Color::COLOR_BLUE();
        } else if (!keyIsPresent()) {
            c = Color::COLOR_RED();
        } else {
            c = Color::COLOR_GREEN();
        }
        leds.setColor(line, c);
    }

}

void PupitrePSTJ::onSwitchLine(uint8_t line, boolean isEnable) {
    Serial.print("onSwitchLine ");
    Serial.print((int) line);
    Serial.print(" ");
    Serial.println(isEnable);
    updateLedColor();
}

void PupitrePSTJ::onClick() {

}

void PupitrePSTJ::onLineConnected(uint8_t line) {
    updateLedColor();
    Serial.print("onLineConnected ");
    Serial.println((int) line);
}

void PupitrePSTJ::onLineDiconnected(uint8_t line) {
    updateLedColor();
    Serial.print("onLineDiconnected ");
    Serial.println((int) line);
}

void PupitrePSTJ::update() {
    if (displayDangerCount && displayDangerNextChange < millis()) {
        updateLedColor();
    }

    if (getMode() == MODE_FIRE && isFired() && fireEndTime < millis()) {
        stopFire();
        updateLedColor();
    }

    PupitreBase::update();
}

void PupitrePSTJ::onLineIsReady(uint8_t line) {
    updateLedColor();
    Serial.print("onLineIsReady ");
    Serial.println((int) line);
}

void PupitrePSTJ::onLineIsNotReady(uint8_t line) {
    updateLedColor();
    Serial.print("onLineIsNotReady ");
    Serial.println((int) line);
}
