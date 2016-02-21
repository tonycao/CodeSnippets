#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <iostream>
#include "counter.h"
using namespace std;

template<class T>
class SmartPointer{
    public:
        SmartPointer(T *t):pc(new _counter(1)){
            cout<<"SmartPointer::SmartPointer() invoked use is: "<<pc->use<<endl;
            this->pt = t;
        }

        SmartPointer(SmartPointer<T> &rhs){
            this->pc = rhs.pc;
            this->pt = rhs.pt;
            this->pc->use++;
            cout<<"SmartPointer copy invoked use is: "<<pc->use<<endl;
        }

        ~SmartPointer(){
            pc->use--;
            cout<<"SmartPointer::~SmartPointer() invoked use is: "<<pc->use<<endl;
            if(pc->use == 0){
                delete pt;
                delete pc;
            }
        }

        SmartPointer<T>& operator=(SmartPointer<T> rhs){
            if(rhs == *this){
                return *this;
            }

            this->pt = rhs.pt;
            this->pc = rhs.pc;
            this->pc->use++;
            cout<<"SmartPointer::operator=() invoked use is: "<<pc->use<<endl;
            return *this;
        }

    private:
        T *pt;
        _counter* pc;

};

#endif
