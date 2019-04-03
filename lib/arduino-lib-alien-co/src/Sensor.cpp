//
// Created by ferna on 04/09/2018.
//

#include "Sensor.h"
#include <Arduino.h>

Sensor::Sensor(uint8_t PIN_SENSOR): Sensor(PIN_SENSOR, WITHOUT_PULL_UP) {}

Sensor::Sensor(uint8_t PIN_SENSOR, SensorType type): Sensor(PIN_SENSOR, type, 0){}

Sensor::Sensor(uint8_t PIN_SENSOR, long sensibility) : Sensor(PIN_SENSOR, WITHOUT_PULL_UP, sensibility) {}

Sensor::Sensor(uint8_t PIN_SENSOR, SensorType type, long sensibility): PIN_SENSOR(PIN_SENSOR), sensibility(sensibility), type(type) {

}
Sensor::~Sensor() {}

SensorEventCode Sensor::checkChange() {
    if(lastEventDate + sensibility >= millis()){
        return NONE;
    }

    SensorState valueSensor = (SensorState) digitalRead(PIN_SENSOR);

    if (valueSensor != currentState ) {
        currentState = valueSensor;
        lastEventDate = millis();
        if (currentState == SS_OPENED) {
            return OPEN;
        } else {
            return CLOSE;
        }
    }

    return NONE;
}

SensorState Sensor::getState() {
    return currentState;
}

long Sensor::getSensibility() const {
    return sensibility;
}

void Sensor::setSensibility(long sensibility) {
    Sensor::sensibility = sensibility;
}

void Sensor::init() {
    pinMode(PIN_SENSOR, type);
    checkChange();
}



