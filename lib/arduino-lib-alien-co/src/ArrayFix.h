//
// Created by hugue on 02/04/2019.
//

#ifndef PUPITRE_ARRAYFIX_H
#define PUPITRE_ARRAYFIX_H

#include <stdint.h>

template <class T>
class ArrayFix {
public:
    uint8_t length;
    T* array;
    ArrayFix(const uint8_t size, T *array) : length(size), array(array) {}
    ArrayFix(const uint8_t size) : length(size), array(new T[size]) {}

};


#endif //PUPITRE_ARRAYFIX_H
