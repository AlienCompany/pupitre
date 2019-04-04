//
// Created by hugue on 04/04/2019.
//

#include "PupitreBase.h"
const MultiSensorBinaryValues<4> initDigitalSensorValues = {
        1023, 184, 326, 132, 511, 155, 247, 117, 682, 168, 281, 124,
        409, 144, 220, 111
};

PupitreBase::PupitreBase(
        byte pinLed1, byte pinLed2, byte pinLed3,
        byte pinLedColor1, byte pinLedColor2, byte pinLedColor3,
        byte pinCom1, byte pinCom2, byte pinCom3, byte pinComGnd,
        byte pinFire,
        byte pinClef,
        byte pinBtns,
        byte pinEncoderA, byte pinEncoderB,
        byte pinLcdSda, byte pinLcdScl
        ) : PIN_LED1(pinLed1), PIN_LED2(pinLed2), PIN_LED3(pinLed3),
          PIN_LED_COLOR1(pinLedColor1), PIN_LED_COLOR2(pinLedColor2), PIN_LED_COLOR3(pinLedColor3),
          PIN_COM_1(pinCom1),PIN_COM_2(pinCom2), PIN_COM_3(pinCom3), PIN_COM_GND(pinComGnd),
          PIN_FIRE(pinFire),
          PIN_CLEF(pinClef),
          PIN_BTNS(pinBtns),
          PIN_ENCODER_A(pinEncoderA), PIN_ENCODER_B(pinEncoderB),
          PIN_LCD_SDA(pinLcdSda), PIN_LCD_SCL(pinLcdScl) {

}

void PupitreBase::checkLineStat() {
    if(mode == MODE_SCANING){
        LineStat stat = digitalRead(PIN_COM_1) == LOW ? CONNECTED : DICONNECTED;
        if(stat != statL1){
            statL1 = stat;
            if(stat == CONNECTED){
                onLineConnected(0);
            } else {
                onLineDiconnected(0);
            }
        }
        stat = digitalRead(PIN_COM_2) == LOW ? CONNECTED : DICONNECTED;
        if(stat != statL2){
            statL2 = stat;
            if(stat == CONNECTED){
                onLineConnected(1);
            } else {
                onLineDiconnected(1);
            }
        }

        stat = digitalRead(PIN_COM_3) == LOW ? CONNECTED : DICONNECTED;
        if(stat != statL3){
            statL3 = stat;
            if(stat == CONNECTED){
                onLineConnected(2);
            } else {
                onLineDiconnected(2);
            }
        }
    }
}

void PupitreBase::setMode(PupitreMode mode) {
    if(mode == MODE_FIRE){
        pinMode(PIN_COM_1, OUTPUT);
        digitalWrite(PIN_COM_1, LOW);
        pinMode(PIN_COM_2, OUTPUT);
        digitalWrite(PIN_COM_2, LOW);
        pinMode(PIN_COM_3, OUTPUT);
        digitalWrite(PIN_COM_3, LOW);
        pinMode(PIN_COM_GND, OUTPUT);
        digitalWrite(PIN_COM_GND, LOW);
    } else if (mode == MODE_SCANING){
        pinMode(PIN_COM_1, INPUT_PULLUP);
        pinMode(PIN_COM_2, INPUT_PULLUP);
        pinMode(PIN_COM_3, INPUT_PULLUP);
        pinMode(PIN_COM_GND, OUTPUT);
        digitalWrite(PIN_COM_GND, LOW);
    } else if (mode == MODE_WATING){
        pinMode(PIN_COM_1, INPUT);
        pinMode(PIN_COM_2, INPUT);
        pinMode(PIN_COM_3, INPUT);
        pinMode(PIN_COM_GND, INPUT);

    }
    fireL1 = fireL2 = fireL3 = false;
    PupitreBase::mode = mode;
}

uint8_t PupitreBase::fire() {
    uint8_t res = 0;
    for (uint8_t i = 0 ; i<3;i++) {
        if (lineIsActive(i) && fire(i)){
            res += (uint8_t)1 << i;
        }
    }
    return res;
}

boolean PupitreBase::fire(uint8_t line) {
    if(mode != MODE_FIRE) return false;
    if(!keyIsPresent()) return false;

    switch (line){
        case 0:
            digitalWrite(PIN_COM_1, HIGH);
            fireL1 = true;
            break;
        case 1:
            digitalWrite(PIN_COM_2, HIGH);
            fireL2 = true;
            break;
        case 2:
            digitalWrite(PIN_COM_3, HIGH);
            fireL3 = true;
            break;
    }


}

void PupitreBase::stopFire(uint8_t line) {
    if(!isFired(line))return;
    switch (line){
        case 0:
            digitalWrite(PIN_COM_1, LOW);
            fireL1 = false;
            break;
        case 1:
            digitalWrite(PIN_COM_2, LOW);
            fireL2 = false;
            break;
        case 2:
            digitalWrite(PIN_COM_3, LOW);
            fireL3 = false;
            break;
    }
}

boolean PupitreBase::stopFire() {
    stopFire(0);
    stopFire(1);
    stopFire(2);
}

boolean PupitreBase::isFired(uint8_t line) {
    switch(line){
        case 0: return fireL1;
        case 1: return fireL2;
        case 2: return fireL3;
        default: return false;
    }
}

boolean PupitreBase::isFired() {
    return fireL1 || fireL2 || fireL3;
}

void PupitreBase::init() {
    leds.init();
    multiSensor.init();
    sensorClef.init();
    sensorFire.init();

    setMode(MODE_SCANING);
    checkLineStat();

    sensorClef.checkChange();
    sensorFire.checkChange();
    multiSensor.checkChange();
    for(uint8_t i = 0; i < 3; i++){
        onSwitchLine(i, multiSensor.getState(i) == SS_CLOSED);
    }
}

bool PupitreBase::lineIsActive(uint8_t line) {
    multiSensor.getState().sensor[line] == SS_CLOSED;
}

PupitreMode PupitreBase::getMode() {
    return mode;
}

LineStat PupitreBase::getLineStat(uint8_t line) {
    switch (line){
        case 0:
            return statL1;
        case 1:
            return statL2;
        case 2:
            return statL3;
        default:
            return UNKNOWN;
    }
}

bool PupitreBase::keyIsPresent() {
    sensorClef.getState() == SS_CLOSED;
}

void PupitreBase::update() {

    multiSensor.checkChange();

    SensorEventCode sensorEvent = sensorClef.checkChange();
    if(sensorEvent != NONE){
        if(sensorEvent == CLOSE){
            onKeyInsert();
        } else {
            onKeyRemove();
            stopFire();
        }
    }

    sensorEvent = sensorFire.checkChange();
    if(sensorEvent == CLOSE){
        if(keyIsPresent()){
            onClickFireWithKey();
        } else {
            onClickFireWithoutKey();
        }
    }

    const MultiSensorEventCode<4> &multiSensorEvent = multiSensor.checkChange();
    if(multiSensorEvent.change){
        for(uint8_t i = 0; i < 3; i++){
            if(multiSensorEvent.sensor[i] == OPEN){
                onSwitchLine(i, false);
            } else if(multiSensorEvent.sensor[i] == CLOSE){
                onSwitchLine(i, true);
            }
        }
        if(multiSensorEvent.sensor[3] == CLOSE){
            onClick();
        }
    }

    checkLineStat();

    leds.update();
}
