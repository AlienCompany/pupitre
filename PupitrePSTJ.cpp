//
// Created by hugue on 04/04/2019.
//

#include "PupitrePSTJ.h"

PupitrePSTJ::PupitrePSTJ(byte pinLed1, byte pinLed2, byte pinLed3, byte pinLedColor1, byte pinLedColor2,
                         byte pinLedColor3, byte pinCom1, byte pinCom2, byte pinCom3, byte pinComGnd, byte pinFire,
                         byte pinClef, byte pinBtns, byte pinEncoderA, byte pinEncoderB, byte pinLcdSda, byte pinLcdScl)
        : PupitreBase(pinLed1, pinLed2, pinLed3, pinLedColor1, pinLedColor2, pinLedColor3, pinCom1, pinCom2, pinCom3,
                      pinComGnd, pinFire, pinClef, pinBtns, pinEncoderA, pinEncoderB, pinLcdSda, pinLcdScl) {}

void PupitrePSTJ::onKeyRemove() {
    setMode(MODE_SCANING);
}

void PupitrePSTJ::onKeyInsert() {
    setMode(MODE_FIRE);
}

void PupitrePSTJ::onClickFireWithoutKey() {
    leds.setColor(0, Color::COLOR_BLACK());
    leds.setColor(1, Color::COLOR_BLACK());
    leds.setColor(2, Color::COLOR_BLACK());
}

void PupitrePSTJ::onClickFireWithKey() {
    if(fire()){
        fireStartTime = millis();
        fireEndTime = fireStartTime + fireDuration;
        updateLedColor();
    }else{
        danger();
    }
}

void PupitrePSTJ::danger() {
    displayDangerCount = 10;
    updateLedColor();
}

void PupitrePSTJ::updateLedColor() {
    if(displayDangerCount){
        if(displayDangerNextChange < millis()) return;
        displayDangerCount--;
        if(displayDangerCount){
            displayDangerNextChange += 200;
            Color c = displayDangerCount & (uint32_t)1 ? Color::COLOR_BLACK() : Color::COLOR_RED();
            leds.setColor(0,c);
            leds.setColor(1,c);
            leds.setColor(2,c);
            return;
        }
    }

    for(uint8_t line = 0; line < 3 ; line++){
        Color c;
        if(isFired(line)){
            c = Color::COLOR_RED();
        } else if(!lineIsActive(line)){
            c = Color::COLOR_BLACK();
        } else if(getLineStat(line) == DICONNECTED){
            c = Color::COLOR_ORANGE();
        } else if(!keyIsPresent()){
            c = Color::COLOR_BLUE();
        } else {
            c = Color::COLOR_GREEN();
        }
        leds.setColor(line, c);
    }

}

void PupitrePSTJ::onSwitchLine(uint8_t line, boolean isEnable) {
    updateLedColor();
}

void PupitrePSTJ::onClick() {

}

void PupitrePSTJ::onLineConnected(uint8_t line) {
    updateLedColor();
}

void PupitrePSTJ::onLineDiconnected(uint8_t line) {
    updateLedColor();
}

void PupitrePSTJ::update() {
    if(displayDangerCount && displayDangerNextChange < millis()){
        updateLedColor();
    }

    if(getMode() == MODE_FIRE && isFired() && fireEndTime < millis()){
        stopFire();
        updateLedColor();
    }

    PupitreBase::update();
}
