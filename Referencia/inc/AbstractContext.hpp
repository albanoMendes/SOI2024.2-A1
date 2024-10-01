#ifndef _ABSTRACTCONTEXT_CLASS_H
#define _ABSTRACTCONTEXT_CLASS_H
#include <stdint.h>

class AbstractContext {
	private:
    	uint64_t sp = 0;
    	uint64_t pc = 0;
	public:
		~AbstractContext();
		void setSp(uint64_t sp_);
		void setPc(uint64_t pc_);
		uint64_t getSp(void);
		uint64_t getPc(void);
};
#endif
