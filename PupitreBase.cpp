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
          PIN_LINE_1(pinCom1),PIN_LINE_2(pinCom2), PIN_LINE_3(pinCom3), PIN_LINE_COM(pinComGnd),
          PIN_FIRE(pinFire),
          PIN_CLEF(pinClef),
          PIN_BTNS(pinBtns),
          PIN_ENCODER_A(pinEncoderA), PIN_ENCODER_B(pinEncoderB),
          PIN_LCD_SDA(pinLcdSda), PIN_LCD_SCL(pinLcdScl) {

}

void PupitreBase::checkLineStat() {

    if(mode == MODE_SCANING){

        static uint32_t nextStep = 0;
        if(nextStep > millis()) return;
        nextStep = millis() + 5;

        static uint8_t currentStep = 0;
        static uint8_t currentLine = 0;
        static bool currentLineIsConnected = false;

        if(currentStep == 0){
            byte pin = getLinePin(currentLine);
            pinMode(pin, INPUT_PULLUP);
            currentStep = 1;
        } else if(currentStep == 1){
            byte pin = getLinePin(currentLine);
            currentLineIsConnected = digitalRead(pin) == LOW;
            if(currentLineIsConnected){
                digitalWrite(PIN_LINE_COM, HIGH);
                pinMode(pin, INPUT);
                currentStep = 2;
            } else {
                LineStat oldStat = getLineStat(currentLine);
                if(oldStat != DISCONNECTED){
                    setLineStat(currentLine, DISCONNECTED);
                    if(oldStat == READY){
                        onLineIsNotReady(currentLine);
                    }
                    onLineDiconnected(currentLine);
                }
                currentStep = 3;
            }
        } else if(currentStep == 2){

            bool isReady = digitalRead(getLinePin(currentLine)) == HIGH;
            LineStat oldStat = getLineStat(currentLine);
            setLineStat(currentLine, isReady ? READY: CONNECTED);
            if(oldStat == DISCONNECTED){
                onLineConnected(currentLine);
            }
            if(isReady && oldStat == CONNECTED){
                onLineIsReady(currentLine);
            }
            if(!isReady && oldStat == READY){
                onLineIsNotReady(currentLine);
            }
            currentStep = 3;

        } else if(currentStep == 3){

            pinMode(getLinePin(currentLine), INPUT);
            pinMode(PIN_LINE_COM, OUTPUT);
            digitalWrite(PIN_LINE_COM, LOW);
            currentLine++;
            if(currentLine == 3)currentLine = 0;
            currentStep = 0;

        }
    }
}

void PupitreBase::setMode(PupitreMode mode) {
    Serial.print("set mode to: ");
    if(mode == MODE_FIRE){
        Serial.println("FIRE");
        pinMode(PIN_LINE_1, OUTPUT);
        digitalWrite(PIN_LINE_1, LOW);
        pinMode(PIN_LINE_2, OUTPUT);
        digitalWrite(PIN_LINE_2, LOW);
        pinMode(PIN_LINE_3, OUTPUT);
        digitalWrite(PIN_LINE_3, LOW);
        pinMode(PIN_LINE_COM, OUTPUT);
        digitalWrite(PIN_LINE_COM, LOW);
    } else if (mode == MODE_SCANING){
        Serial.println("SCANING");
        pinMode(PIN_LINE_1, INPUT);
        pinMode(PIN_LINE_2, INPUT);
        pinMode(PIN_LINE_3, INPUT);
        pinMode(PIN_LINE_COM, OUTPUT);
        digitalWrite(PIN_LINE_COM, LOW);
    } else if (mode == MODE_WATING){
        Serial.println("WATING");
        pinMode(PIN_LINE_1, INPUT);
        pinMode(PIN_LINE_2, INPUT);
        pinMode(PIN_LINE_3, INPUT);
        pinMode(PIN_LINE_COM, INPUT);

    }
    fireL1 = fireL2 = fireL3 = false;
    PupitreBase::mode = mode;
}

uint8_t PupitreBase::fire() {
    uint8_t res = 0;
    for (uint8_t i = 0 ; i<3;i++) {
        if (!lineIsActive(i)){
            Serial.print("LINE NOT ACTIVE: ");
            Serial.println(i);

        }else if(fire(i)){
            Serial.print("FIRE IN LINE ");
            Serial.println(i);
            res += (uint8_t)1 << i;
        } else{
            Serial.print("FIRE CANCELED ");
            Serial.println(i);
        }
    }
    return res;
}

boolean PupitreBase::fire(uint8_t line) {
    if(mode != MODE_FIRE){
        Serial.println("FIRE CANCELLED: Not in fire mode");
        return false;
    }
    if(!keyIsPresent()) {
        Serial.println("FIRE CANCELLED: Key not present");
        return false;
    }

    switch (line){
        case 0:
            digitalWrite(PIN_LINE_1, HIGH);
            fireL1 = true;
            return true;
        case 1:
            digitalWrite(PIN_LINE_2, HIGH);
            fireL2 = true;
            return true;
        case 2:
            digitalWrite(PIN_LINE_3, HIGH);
            fireL3 = true;
            return true;
        default:
            return false;
    }


}

void PupitreBase::stopFire(uint8_t line) {
    if(!isFired(line))return;
    switch (line){
        case 0:
            digitalWrite(PIN_LINE_1, LOW);
            fireL1 = false;
            break;
        case 1:
            digitalWrite(PIN_LINE_2, LOW);
            fireL2 = false;
            break;
        case 2:
            digitalWrite(PIN_LINE_3, LOW);
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
    return multiSensor.getState().sensor[line] == SS_CLOSED;
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

void PupitreBase::setLineStat(uint8_t line, LineStat stat) {
    switch (line){
        case 0:
            statL1 = stat;
            break;
        case 1:
            statL2 = stat;
            break;
        case 2:
            statL3 = stat;
            break;
    }
}

bool PupitreBase::keyIsPresent() {
    return sensorClef.getState() == SS_CLOSED;
}

void PupitreBase::update() {

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

    const MultiSensorEventCode<4> multiSensorEvent = multiSensor.checkChange();
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
