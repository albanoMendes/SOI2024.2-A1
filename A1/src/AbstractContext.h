#ifndef ABSTRACTCONTEXT_H
#define ABSTRACTCONTEXT_H

#include <cstdint>

class AbstractContext {
public:
    uint32_t sp;
    uint32_t st;

    AbstractContext(uint32_t sp, uint32_t st);
};

#endif
