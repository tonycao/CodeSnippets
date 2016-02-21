#ifndef COUNTER_H
#define COUNTER_H

#include "smartpointer.h"

class _counter{
    template<class T> friend class SmartPointer;
    _counter(int u):use(u){}
    ~_counter(){}
    int use;
};


#endif
