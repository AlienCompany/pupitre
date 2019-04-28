//
// Created by hugue on 28/04/2019.
//

#include "Timer.h"

template<class... Args>
Chain<Timer<Args...> *> Timer<Args...>::chain = Chain<Timer<Args...> *>();