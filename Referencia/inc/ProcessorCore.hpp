#ifndef _PROCESSCORE_CLASS_HPP
#define _PROCESSCORE_CLASS_HPP

#include "AbstractContext.hpp"


class ProcessorCore {
	private:
		AbstractContext *context;
	public:
		void setContext(AbstractContext *cont_);
		AbstractContext* currentContext();
		AbstractContext* getOutContext();
};

#endif
