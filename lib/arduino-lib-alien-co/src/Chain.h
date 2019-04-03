//
// Created by hugues on 08/09/2018.
//

#ifndef LETTER_BOX_CHAIN_H
#define LETTER_BOX_CHAIN_H

#include <Arduino.h>
#include "ChainElement.h"

template <class T>
class Chain {
private:
    ChainElement<T>* first;
    ChainElement<T>* last;
public:
    Chain();

    virtual ~Chain();

    ChainElement<T> * pushFront(T value);
    ChainElement<T> * pushBack(T value);

    T removeFirst();
    T removeLast();

    T remove(ChainElement<T> *element);

    ChainElement<T> *getFirst() const;

    ChainElement<T> *getLast() const;

    uint16_t length() const;

};

#endif //LETTER_BOX_CHAIN_H
