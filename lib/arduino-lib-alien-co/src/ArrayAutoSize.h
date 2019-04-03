//
// Created by hugues on 13/07/2018.
//

#ifndef MARVIN_ARRAYAUTOSIZE_H
#define MARVIN_ARRAYAUTOSIZE_H

#include <Arduino.h>
#include <stdint-gcc.h>

template <typename T>
class ArrayAutoSize{
private:
    T* array;
    uint16_t size; // sizeof array
    uint16_t length; // nb ellement in array
    static const float RESIZE_SCAL = 2.;
    static const uint16_t INIT_SIZE = 8;
    void resize(uint16_t newSize);

    void resize();

public:

    ArrayAutoSize(uint16_t initSize);

    ArrayAutoSize();

    virtual ~ArrayAutoSize();

    T get(uint16_t pos) const;

    uint16_t pushBack(const T &value);

    int32_t indexOf(const T &value) const;

    void set(uint16_t pos, const T &value);

    uint16_t getLength() const;

    T removeLast();

    void removeLasts(uint16_t nbToRemove);

    T last() const;

    T first() const;

};


#endif //MARVIN_ARRAYAUTOSIZE_H
