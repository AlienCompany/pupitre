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

    virtual void execute() = 0;

    TimerExecutable(
        uint32_t nextExecute,
        uint32_t interval
    ): nextExecute(nextExecute),
            interval(interval){
        id = idInc++;
    }
};



template<typename... Args>
class TimerE : public TimerExecutable{
public:
    static const int size = sizeof...(Args);
    uint8_t* data = NULL;

    void (*func)(Args ...);

    void execute() override {

        func(((Args) (*data))...);
    }
//    Args2...* args;

    TimerE(
            uint32_t nextExecute,
            uint32_t interval,
            void (*f)(Args ...),
            Args... args
    ) : TimerExecutable(nextExecute, interval){
        func = f;
        id = TimerExecutable::idInc++;
        data = new uint8_t[size]{ args...};
    }
};




class Timer{
private:
    static Chain<TimerExecutable *> chain;
public:

    template<typename... Args>
    static uint16_t setInterval(size_t interval, const void (*f)(Args &...), Args ... args) {
        TimerExecutable *t = new TimerE<Args...>(millis() + interval, interval, f, args...);
        chain.pushBack(t);
        return t->id;
    }

    template<typename... Args>
    static uint16_t setTimeOut(size_t time, void (*f)(Args ...), Args ... args) {
        TimerExecutable *t = new TimerE<Args...>(millis() + time, 0, f, args...);
        chain.pushBack(t);
        return t->id;
    }

    static void check() {
        TimerExecutable* v = chain.getFirst()->getValue();
        if (v->nextExecute < millis()) {
            v->execute();
            chain.removeFirst();
            if (v->interval) {
                v->nextExecute += v->interval;
                ChainElement<TimerExecutable *> *e = chain.getFirst();
                while (e != NULL && e->getValue()->nextExecute < v->nextExecute) {
                    e = e->getNext();
                }
                if (e == NULL) {
                    chain.pushBack(v);
                } else {
                    e->setPrevious(v);
                }
            }
        }
    }
};

#endif //PUPITRE_TIMER_H
