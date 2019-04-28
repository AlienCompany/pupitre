//
// Created by hugue on 28/04/2019.
//

#include <Arduino.h>
#include "Chain.h"
#include "ChainElement.h"

#ifndef PUPITRE_TIMER_H
#define PUPITRE_TIMER_H

class TimerExecutable {
public:
    static uint16_t idInc;
    uint16_t id;
    uint32_t nextExecute;
    uint32_t interval;
    void (*func)();

    virtual void execute() {
        func();
    }

    TimerExecutable(
        uint32_t nextExecute,
        uint32_t interval,
        void (*f)()
    ): nextExecute(nextExecute),
            interval(interval){
        id = idInc++;
        func = f;
    }
};

class Timer{
private:
    static Chain<TimerExecutable *> chain;
public:

    static uint16_t setInterval(size_t interval, void (*f)()) {
        TimerExecutable *t = new TimerExecutable(millis() + interval, interval, f);
        insertOnChain(t);
        return t->id;
    }

    template<typename... Args>
    static uint16_t setTimeOut(size_t interval, void (*f)()) {
        TimerExecutable *t = new TimerExecutable(millis() + interval, 0, f);
        insertOnChain(t);
        return t->id;
    }

    static void check() {
        TimerExecutable* v = chain.getFirst()->getValue();
        if (v->nextExecute < millis()) {
            v->execute();
            chain.removeFirst();
            if (v->interval) {
                v->nextExecute += v->interval;
                insertOnChain(v);
            }
        }
    }

    static void insertOnChain(TimerExecutable* v){
        ChainElement<TimerExecutable *> *e = chain.getFirst();
        while (e != NULL && e->getValue()->nextExecute < v->nextExecute) {
            e = e->getNext();
        }
        if (e == NULL) {
            chain.pushBack(v);
        } if(chain.getFirst() == e) {
            chain.pushFront(v);
        } else {
            e->setPrevious(v);
        }
    }
};

#endif //PUPITRE_TIMER_H
