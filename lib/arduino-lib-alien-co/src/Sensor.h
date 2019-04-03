//
// Created by ferna on 04/09/2018.
//

#ifndef LETTER_BOX_SENSOR_H
#define LETTER_BOX_SENSOR_H

#include <stdint-gcc.h>
#include <Arduino.h>
#include "SensorState.h"

enum SensorType {
    WITH_PULL_UP = INPUT_PULLUP,
    WITHOUT_PULL_UP = INPUT
};

class Sensor {

private:
    uint8_t PIN_SENSOR;
    SensorType type;
    SensorState currentState;
    long lastEventDate = 0; // in ms
    long sensibility = 0; //in ms

public:
    Sensor(uint8_t PIN_SENSOR);

    Sensor(uint8_t PIN_SENSOR, SensorType type);

    Sensor(uint8_t PIN_SENSOR, long sensibility);

    Sensor(uint8_t PIN_SENSOR, SensorType type, long sensibility);

    virtual ~Sensor();

    SensorEventCode checkChange();

    SensorState getState();

    long getSensibility() const;

    void setSensibility(long sensibility);

    void init();
};


#endif //LETTER_BOX_SENSOR_H
