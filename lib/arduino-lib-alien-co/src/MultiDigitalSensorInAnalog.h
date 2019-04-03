//
// Created by hugue on 02/04/2019.
//

#ifndef PUPITRE_MULTIDIGITALSENSORINANALOG_H
#define PUPITRE_MULTIDIGITALSENSORINANALOG_H

#include <Arduino.h>
#include "ArrayFix.h"
#include "SensorState.h"


template <size_t NB_SENSOR>
struct MultiSensorEventCode {
    boolean change = false;
    SensorEventCode sensor[NB_SENSOR] = {};
};

template <size_t NB_SENSOR>
struct MultiSensorState {
    SensorState sensor[NB_SENSOR];
};

template <size_t NB_SENSOR>
struct MultiSensorBinaryValues {
    uint16_t values[1<<NB_SENSOR];
};

template <size_t NB_SENSOR>
class MultiDigitalSensorInAnalog {
private:
    const byte ANNALOG_PIN;
    MultiSensorBinaryValues<NB_SENSOR> binaryValues;
    const uint8_t lastval = 0;
    uint32_t nextCheck = 0;
    uint32_t sensibility = 100;

    uint16_t _abs(int16_t value){
        return value<0?-value:value;
    }

    uint8_t convertAnnalogToBinarys(uint16_t val){
        uint8_t resI = 0;
        uint16_t resD = val;
        for(uint8_t i = 1; i < (1 << NB_SENSOR) ; i++){
            uint16_t dist = _abs((int16_t)(binaryValues.values[i] - val));
            if(dist<resD){
                resD = dist;
                resI = i;
            }
        }
        return resI;
    }


public:
    MultiDigitalSensorInAnalog(const byte annalogPin, const MultiSensorBinaryValues<NB_SENSOR> &binaryValues)
            : ANNALOG_PIN(annalogPin), binaryValues(binaryValues) {}


    MultiSensorEventCode<NB_SENSOR> checkChange(){
        if(nextCheck > millis()) return MultiSensorEventCode<NB_SENSOR>()
        uint8_t newVal = convertAnnalogToBinarys(analogRead(ANNALOG_PIN));
        if(newVal == lastval) return MultiSensorEventCode<NB_SENSOR>();

        MultiSensorEventCode<NB_SENSOR>res;
        res.change = true;
        for(uint8_t i =0; i <NB_SENSOR; i++){
            res.sensor[i] = newVal - lastval;
        }

        nextCheck += sensibility;

        return res;

    }

    MultiSensorState<NB_SENSOR> getState(){
        MultiSensorState<NB_SENSOR> res();
        for(uint8_t i =0; i <NB_SENSOR; i++){
            res.sensor[i] = (lastval>>i)&1;
        }
        return res;
    }

    uint32_t getSensibility() const {
        return sensibility;
    }

    void setSensibility(uint32_t sensibility) {
        MultiDigitalSensorInAnalog::sensibility = sensibility;
    }

    void init(){

        // for emit change for each
        lastval = convertAnnalogToBinarys(analogRead(ANNALOG_PIN));
        lastval ^= (1 << NB_SENSOR)-1;
    }
};


#endif //PUPITRE_MULTIDIGITALSENSORINANALOG_H
