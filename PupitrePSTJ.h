//
// Created by hugue on 04/04/2019.
//

#ifndef PUPITRE_PUPITREPSTJ_H
#define PUPITRE_PUPITREPSTJ_H


#include "PupitreBase.h"

class PupitrePSTJ : public PupitreBase {
private:
    uint32_t fireDuration = 0;
    uint32_t fireStartTime = 0;
    uint32_t fireEndTime = 0;

    uint32_t displayDangerCount = 0;
    uint32_t displayDangerNextChange = 0;

public:
    PupitrePSTJ(byte pinLed1, byte pinLed2, byte pinLed3, byte pinLedColor1, byte pinLedColor2, byte pinLedColor3,
                byte pinCom1, byte pinCom2, byte pinCom3, byte pinComGnd, byte pinFire, byte pinClef, byte pinBtns,
                byte pinEncoderA, byte pinEncoderB, byte pinLcdSda, byte pinLcdScl);

protected:
    void onKeyRemove() override;

    void onKeyInsert() override;

    void onClickFireWithoutKey() override;

    void onClickFireWithKey() override;

    void danger();

    void updateLedColor();

    void onSwitchLine(uint8_t line, boolean isEnable) override;

    void onClick() override;

    void onLineConnected(uint8_t line) override;

    void onLineDiconnected(uint8_t line) override;

public:
    virtual void update();

};


#endif //PUPITRE_PUPITREPSTJ_H
