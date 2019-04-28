//
// Created by hugues on 08/09/2018.
//

#ifndef LETTER_BOX_CHAIN_ELEMENT_H
#define LETTER_BOX_CHAIN_ELEMENT_H

#include <stddef.h>

template <typename T>
class ChainElement {
private:
    T value;
    ChainElement<T>* previous;
    ChainElement<T>* next;
public:
    ChainElement(T value);

    virtual ~ChainElement();

    T getValue() const;

    void setValue(T value);

    ChainElement *getPrevious() const;

    void setPrevious(ChainElement *previous);
    void setPrevious(const T &el);

    ChainElement *getNext() const;

    void setNext(ChainElement *next);
    void setNext(const T &el);

};


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
    value = value;
}

template<typename T>
ChainElement<T> *ChainElement<T>::getPrevious() const {
    return previous;
}

template<typename T>
void ChainElement<T>::setPrevious(ChainElement *previous) {
    previous = previous;
}

template<typename T>

void ChainElement<T>::setPrevious(const T &el) {
    ChainElement<T>* e = new ChainElement(el);
    e->setNext(this);
    e->setPrevious(previous);
    this->setPrevious(e);
}

template<typename T>
ChainElement<T> *ChainElement<T>::getNext() const {
    return next;
}

template<typename T>
void ChainElement<T>::setNext(ChainElement *next) {
    next = next;
}

template<typename T>
void ChainElement<T>::setNext(const T &el) {
    ChainElement<T>* e = new ChainElement(el);
    e->setNext(next);
    e->setPrevious(this);
    this->setNext(e);
}

#endif //LETTER_BOX_CHAIN_ELEMENT_H
