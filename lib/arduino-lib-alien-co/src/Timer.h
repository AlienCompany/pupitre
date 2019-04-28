//
// Created by hugue on 28/04/2019.
//

#include <Arduino.h>
#include "Chain.h"

#ifndef PUPITRE_TIMER_H
#define PUPITRE_TIMER_H


template<class... Args>
class Timer : public Args ... {
private:
    static Chain<Timer *> chain;
    static uint16_t idInc;
    uint16_t id;
    uint32_t nextExecute;
    uint32_t interval;

    void (*func)(Args &...);

    void execute() {
        func(((Args) this)...);
    }
//    Args2...* args;

    Timer(
            uint32_t nextExecute,
            uint32_t interval,
            const void (*f)(Args &...),
            const Args &... args
    ) : nextExecute(nextExecute),
    interval(interval),
    Args(args)...,
    id(idInc++){
        func = f;
    }

public:

    static uint16_t setInterval(size_t interval, const void (*f)(Args &...), const Args &... args) {
        Timer *t = new Timer(millis() + interval, interval, f, args...);
        Timer<Args...>::chain.pushBack(t);
        return t->id;
    }

    static void setTimeOut(size_t time, const void (*f)(Args &...), const Args &... args) {
        Timer *t = new Timer(millis() + time, 0, f, args...);
        Timer<Args...>::chain.pushBack(t);
        return t->id;
    }

    static void check() {
        ChainElement<Timer> v = chain.getFirst()->getValue();
        if (v->nextExecute < millis()) {
            v->execute();
            chain.removeFirst();
            if (v->interval) {
                v->nextExecute += v->interval;
                ChainElement<Timer *> *e = &chain.getFirst();
                while (e != NULL && e->getValue()->nextExecute < v->nextExecute) {
                    e = e->getNext();
                }
                if (e == NULL) {
                    chain.pushBack(v);
                } else {
                    e.setPrevious(v);
                }
            }
        }
    }
};


#endif //PUPITRE_TIMER_H
