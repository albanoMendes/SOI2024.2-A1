#ifndef PROCESSCORE_H
#define PROCESSCORE_H

#include <iostream>
#include "AbstractContext.h"

class ProcessCore {
public:
    AbstractContext* CurrentContext; // O contexto atual do processador

    AbstractContext* getContext() {
        return CurrentContext;
    }

    void setContext(AbstractContext* c) {
        CurrentContext = c;
    }
};

#endif