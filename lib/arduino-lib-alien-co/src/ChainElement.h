//
// Created by hugues on 08/09/2018.
//

#ifndef LETTER_BOX_CHAIN_ELEMENT_H
#define LETTER_BOX_CHAIN_ELEMENT_H

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

    ChainElement *getNext() const;

    void setNext(ChainElement *next);

};



#endif //LETTER_BOX_CHAIN_ELEMENT_H
