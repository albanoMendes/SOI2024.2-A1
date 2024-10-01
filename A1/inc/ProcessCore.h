#ifndef _PROCESSCORE_CLASS_H
#define _PROCESSCORE_CLASS_H

#include "AbstractContext.h"

class ProcessorCore {
	private:
		AbstractContext *context;
	public:
		~ProcessorCore();
		void setContext(AbstractContext *cont_);
		AbstractContext* currentContext();
		AbstractContext* getOutContext();
};

#endif