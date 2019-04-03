#include <Arduino.h>
#include <Led.h>
#include <Sensor.h>
#include <ArrayFix.h>
#include <MultiplexLed.h>
#include <MultiDigitalSensorInAnalog.h>

// Pin CONFIG:

Sensor sensorClef(12, WITH_PULL_UP);
Sensor sensorFire(11, WITH_PULL_UP);

const byte PIN_LED_GROUP[] = {6, 7, 8};
const byte PIN_LED_COLOR[] = {9, 10, 11};
MultiplexLed leds = MultiplexLed(ArrayFix<const byte>(3, PIN_LED_GROUP), ArrayFix<const byte>(3, PIN_LED_COLOR));

const MultiSensorBinaryValues<4> initDigitalSensorValues = {1023, 184, 326, 132, 511, 155, 247, 117, 682, 168, 281, 124,
                                                            409, 144, 220, 111};

MultiDigitalSensorInAnalog<4> multiSensor = MultiDigitalSensorInAnalog<4>(A0, initDigitalSensorValues);

const Color ORANGE = Color(0xFFFFFF);
const Color WHITE = Color(85,187,255);
const Color RED = Color(0xFF0000);
const Color GREEN = Color(0x00FF00);
const Color BLUE = Color(0x0000FF);
const Color BLACK = Color(0);


void setup() {
    Serial.begin(9600);
    leds.init();
    multiSensor.init();
}

void loop() {

    MultiSensorEventCode<4> multiSensorRes;

    if(Serial.available()){
        delay(10);
        uint8_t l = Serial.readStringUntil(',').toInt();
        uint8_t r = Serial.readStringUntil(',').toInt();
        uint8_t g = Serial.readStringUntil(',').toInt();
        uint8_t b = Serial.readStringUntil(',').toInt();
        Color c = Color(r,g,b);
        leds.setColor(l,c);
    }

    if ((multiSensorRes = multiSensor.checkChange()).change) {
        Serial.print(multiSensor.getState().sensor[0]);
        Serial.print(multiSensor.getState().sensor[1]);
        Serial.print(multiSensor.getState().sensor[2]);
        Serial.println(multiSensor.getState().sensor[3]);
        if (multiSensorRes.sensor[0] != NONE) {
            Serial.print("set color of led 0 : ");
            Serial.println(multiSensorRes.sensor[0]);
            leds.setColor(0, multiSensorRes.sensor[0] == CLOSE ? GREEN : RED);
        }
        if (multiSensorRes.sensor[1] != NONE) {
            Serial.print("set color of led 1 : ");
            Serial.println(multiSensorRes.sensor[1] == CLOSE);
            leds.setColor(1, multiSensorRes.sensor[1] == CLOSE ? GREEN : RED);
        }
        if (multiSensorRes.sensor[2] != NONE) {
            Serial.print("set color of led 2 : ");
            Serial.println(multiSensorRes.sensor[2] == CLOSE);
            leds.setColor(2, multiSensorRes.sensor[2] == CLOSE ? GREEN : RED);
        } else if (multiSensorRes.sensor[3] == CLOSE) {
            Serial.println("BTN 1 CLOSE");
            for(uint8_t i = 0 ; i < 3 ;i++){
                leds.setColor(i, leds.getColor(i).value() >> 8);
            }
        } else if (multiSensorRes.sensor[3] == OPEN) {
            Serial.println("BTN 1 OPEN");
            for(uint8_t i = 0 ; i < 3 ;i++){
                leds.setColor(i, leds.getColor(i).value() << 8);
            }
        }
    }


    leds.update();
}
