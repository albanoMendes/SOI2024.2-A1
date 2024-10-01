#ifndef _A1CONTEXT_CLASS_H
#define _A1CONTEXT_CLASS_H
#include <stdint.h>
#include "AbstractContext.h"

class A1Context : public AbstractContext {
	private:
    	uint64_t r1 = 0;
    	uint64_t r2 = 0;
    	uint64_t r3 = 0;
    	uint64_t r4 = 0;
    	uint64_t r5 = 0;
    	uint64_t r0 = 0;
    	uint64_t st = 0;
	public:
		void setR1(uint64_t r1_);
		void setR2(uint64_t r2_);
		void setR3(uint64_t r3_);
		void setR4(uint64_t r4_);
		void setR5(uint64_t r5_);
		void setR0(uint64_t r0_);
		uint64_t getR1(void);
		uint64_t getR2(void);
		uint64_t getR3(void);
		uint64_t getR4(void);
		uint64_t getR5(void);
		uint64_t getR0(void);
};
#endif
