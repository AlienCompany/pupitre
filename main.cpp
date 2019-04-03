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

    if ((multiSensorRes = multiSensor.checkChange()).change) {
        }
    }

    leds.update();
}
