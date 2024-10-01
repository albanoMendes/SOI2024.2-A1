#include "AbstractContext.h"
// #include <stdint>

void AbstractContext::setSp(uint64_t sp_){
	sp = sp_;
}
void AbstractContext::setPc(uint64_t pc_){
	pc = pc_;
}
uint64_t AbstractContext::getSp(void){
	return sp;
}
uint64_t AbstractContext::getPc(void){
	return pc;
}