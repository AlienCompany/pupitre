//
// Created by hugues on 08/09/2018.
//

#include <stddef.h>
#include "Chain.h"

template<typename T>
Chain<T>::Chain() {
    this->first = NULL;
    this->last = NULL;
}

template<typename T>
Chain<T>::~Chain() {
}

template<typename T>
ChainElement<T> *Chain<T>::getFirst() const {
    return first;
}

template<typename T>
ChainElement<T> *Chain<T>::getLast() const {
    return last;
}

template<typename T>
ChainElement<T> *Chain<T>::pushFront(T value) {
    ChainElement<T> *newEle = new ChainElement<T>(value);
    if(first == NULL){
        last = newEle;
    }else{
        newEle->setNext(first);
        first->setPrevious(newEle);
    }
    first = newEle;
}

template<typename T>
ChainElement<T> *Chain<T>::pushBack(T value) {
    ChainElement<T> *newEle = new ChainElement<T>(value);
    if(last == NULL){
        first = newEle;
    }else{
        newEle->setPrevious(last);
        last->setNext(newEle);
    }
    last = newEle;
}

template<typename T>
T Chain<T>::removeFirst() {
    return remove(first);
}

template<typename T>
T Chain<T>::removeLast() {
    return remove(last);
}

template<typename T>
T Chain<T>::remove(ChainElement<T> *element) {

    if(element->getNext() != NULL) element->getNext()->setPrevious(element->getPrevious());
    if(element->getPrevious() != NULL) element->getPrevious()->setNext(element->getNext());
    if(element == last) last = element->getPrevious();
    if(element == first) first = element->getNext();
    T res = element->getValue();
    delete element;
    return NULL;
}

template<typename T>
uint16_t Chain<T>::length() const {
    int length = 0;
    ChainElement<T>* element = this->first;
    for(;element != NULL; element = element->getNext())length++;
    return length;
}
