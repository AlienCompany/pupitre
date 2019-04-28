//
// Created by hugue on 28/04/2019.
//

#include "Timer.h"
#include "Chain.h"

//template class Chain<TimerExecutable *>;
//template class ChainElement<TimerExecutable *>;

Chain<TimerExecutable *> Timer::chain = Chain<TimerExecutable *>();
uint16_t TimerExecutable::idInc = 0;