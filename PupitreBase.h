//
// Created by hugue on 04/04/2019.
//

#ifndef PUPITRE_PUPITREBASE_H
#define PUPITRE_PUPITREBASE_H


#include <USBAPI.h>
#include <Sensor.h>
#include <MultiDigitalSensorInAnalog.h>
#include <MultiplexLed.h>

extern const MultiSensorBinaryValues<4> initDigitalSensorValues;

enum PupitreMode{
    MODE_WATING = 0,
    MODE_FIRE = 1,
    MODE_SCANING = 2
};


enum LineStat{
    UNKNOWN = 0,
    DISCONNECTED = 1,
    CONNECTED = 2,
    READY = 3
};

class PupitreBase {
private:
    byte PIN_LED1;
    byte PIN_LED2;
    byte PIN_LED3;
    byte PIN_LED_COLOR1;
    byte PIN_LED_COLOR2;
    byte PIN_LED_COLOR3;
    byte PIN_LINE_1;
    byte PIN_LINE_2;
    byte PIN_LINE_3;
    byte PIN_LINE_COM;
    byte PIN_FIRE;
    byte PIN_CLEF;
    byte PIN_BTNS;
    byte PIN_ENCODER_A;
    byte PIN_ENCODER_B;
    byte PIN_LCD_SDA;
    byte PIN_LCD_SCL;

    PupitreMode mode = MODE_WATING;

    LineStat statL1 = UNKNOWN;
    LineStat statL2 = UNKNOWN;
    LineStat statL3 = UNKNOWN;

    boolean fireL1 = false;
    boolean fireL2 = false;
    boolean fireL3 = false;

protected:
    Sensor sensorClef = Sensor(PIN_CLEF, WITH_PULL_UP);
    Sensor sensorFire = Sensor(PIN_FIRE, WITH_PULL_UP);

    MultiplexLed leds = MultiplexLed(
            ArrayFix<const byte>(3, new byte[3]{PIN_LED1, PIN_LED2, PIN_LED3}),
            ArrayFix<const byte>(3, new byte[3]{PIN_LED_COLOR1, PIN_LED_COLOR2, PIN_LED_COLOR3})
    );


    MultiDigitalSensorInAnalog<4> multiSensor = MultiDigitalSensorInAnalog<4>(PIN_BTNS, initDigitalSensorValues);

    virtual void onLineConnected(uint8_t line) = 0;
    virtual void onLineDiconnected(uint8_t line) = 0;
    virtual void onLineIsReady(uint8_t line) = 0;
    virtual void onLineIsNotReady(uint8_t line) = 0;

    virtual void onKeyRemove() = 0;
    virtual void onKeyInsert() = 0;
    virtual void onClickFireWithoutKey() = 0;
    virtual void onClickFireWithKey() = 0;

    virtual void onSwitchLine(uint8_t line, boolean isEnable) = 0;
    // virtual void onTurn(int8_t rotate) = 0;
    virtual void onClick() = 0;
    
public:
    PupitreBase(byte pinLed1, byte pinLed2, byte pinLed3, byte pinLedColor1, byte pinLedColor2, byte pinLedColor3,
                byte pinCom1, byte pinCom2, byte pinCom3, byte pinComGnd, byte pinFire, byte pinClef, byte pinBtns,
                byte pinEncoderA, byte pinEncoderB, byte pinLcdSda, byte pinLcdScl);

public:


    void setMode(PupitreMode mode);

    virtual uint8_t fire();

    virtual boolean fire(uint8_t line);

    void stopFire(uint8_t line);

    boolean stopFire();

    boolean isFired(uint8_t line);

    boolean isFired();

    virtual void checkLineStat();

    virtual void init();

    bool lineIsActive(uint8_t line);

    PupitreMode getMode();

    LineStat getLineStat(uint8_t line);

    bool keyIsPresent();

    byte getLinePin(uint8_t line){
        switch (line){
            case 0:
                return PIN_LINE_1;
            case 1:
                return PIN_LINE_2;
            case 2:
                return PIN_LINE_3;
            default:
                return 0;
        }
    }

    virtual void update();

    void setLineStat(uint8_t line, LineStat stat);
};


#endif //PUPITRE_PUPITREBASE_H
