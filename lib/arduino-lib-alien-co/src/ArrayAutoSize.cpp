//
// Created by hugues on 13/07/2018.
//

#include "ArrayAutoSize.h"

template<typename T>
void ArrayAutoSize<T>::resize(uint16_t newSize) {
    T *oldArray = array;
    array = new T[size = newSize];
    memcpy(array, oldArray, length);
    delete oldArray;
}

template<typename T>
void ArrayAutoSize<T>::resize() {
    resize((uint16_t) (size * RESIZE_SCAL));
}

template<typename T>
ArrayAutoSize<T>::ArrayAutoSize(uint16_t initSize) : size(initSize) {
    array = new T[size];
    length = 0;
}

template<typename T>
ArrayAutoSize<T>::ArrayAutoSize() {
    ArrayAutoSize(INIT_SIZE);
}

template<typename T>
ArrayAutoSize<T>::~ArrayAutoSize() {
    delete array;
}

template<typename T>
T ArrayAutoSize<T>::get(uint16_t pos) const {
    return array[pos];
}

template<typename T>
uint16_t ArrayAutoSize<T>::pushBack(const T &value) {
    if (length == size) resize();
    array[length++] = value;
    return length - 1;
}

template<typename T>
int32_t ArrayAutoSize<T>::indexOf(const T &value) const{
    for (uint16_t i = 0; i < length; i++) {
        if (array[i] == value) return i;
    }
    return -1;
}

template<typename T>
void ArrayAutoSize<T>::set(uint16_t pos, const T &value) {
    if (pos >= length) {
        if (pos >= size) {
            resize(pos + 1);
        }
    }
    array[pos] = value;
}

template<typename T>
uint16_t ArrayAutoSize<T>::getLength() const {
    return length;
}

template<typename T>
T ArrayAutoSize<T>::removeLast() {
    length--;
    return array(length);
}

template<typename T>
void ArrayAutoSize<T>::removeLasts(uint16_t nbToRemove) {
    length -= nbToRemove;
}

template<typename T>
T ArrayAutoSize<T>::last() const {
    return get(length - 1);
}

template<typename T>
T ArrayAutoSize<T>::first() const {
    return get(0);
}
