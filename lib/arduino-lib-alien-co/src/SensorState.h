//
// Created by hugue on 02/04/2019.
//

#ifndef PUPITRE_SENSORSTATE_H
#define PUPITRE_SENSORSTATE_H

enum SensorState {
    SS_OPENED = 1,
    SS_CLOSED = 0
};

enum SensorEventCode {
    CLOSE = 1,
    NONE = 0,
    OPEN = -1
};

#endif //PUPITRE_SENSORSTATE_H
