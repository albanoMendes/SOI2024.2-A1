#ifndef AV015412CONTEXT_H
#define AV015412CONTEXT_H

#include <cstdint>
#include "AbstractContext.h"

class AV015412Context : public AbstractContext {
public:
    uint32_t r0, r1, r2, r3, r4, r5;

    AV015412Context(uint32_t sp, uint32_t st, uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3, uint32_t r4, uint32_t r5)
        : AbstractContext(sp, st) {
        this->r0 = r0;
        this->r1 = r1;
        this->r2 = r2;
        this->r3 = r3;
        this->r4 = r4;
        this->r5 = r5;
    }
};

#endif