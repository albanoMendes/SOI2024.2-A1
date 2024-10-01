#include "ProcessorCore.hpp"
#include "AbstractContext.hpp"

void ProcessorCore::setContext(AbstractContext *cont_){
	context = cont_;
	
}
AbstractContext* ProcessorCore::currentContext(){
	return context;
}
AbstractContext* ProcessorCore::getOutContext(){
	AbstractContext *contxt = context;
	return contxt;
}
