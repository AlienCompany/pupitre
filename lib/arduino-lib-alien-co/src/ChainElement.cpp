//
// Created by hugues on 08/09/2018.
//

#include <stddef.h>
#include "ChainElement.h"


template<typename T>
ChainElement<T>::ChainElement(T value) : value(value) {
    previous = NULL;
    next = NULL;
}

template<typename T>
ChainElement<T>::~ChainElement() {

}

template<typename T>
T ChainElement<T>::getValue() const {
    return value;
}

template<typename T>
void ChainElement<T>::setValue(T value) {
    ChainElement::value = value;
}

template<typename T>
ChainElement<T> *ChainElement<T>::getPrevious() const {
    return previous;
}

template<typename T>
void ChainElement<T>::setPrevious(ChainElement *previous) {
    ChainElement::previous = previous;
}

template<typename T>
ChainElement<T> *ChainElement<T>::getNext() const {
    return next;
}

template<typename T>
void ChainElement<T>::setNext(ChainElement *next) {
    ChainElement::next = next;
}
