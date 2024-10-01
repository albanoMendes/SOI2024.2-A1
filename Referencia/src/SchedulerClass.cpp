#include "SchedulerClass.h"
#include <iostream>


/* Abstract Scheduler methods ------------------------------------------------*/
/**
 * @brief AbstractScheduler constructor
 * @param quanta: Time quanta to be used
 * @returns New object
*/
AbstractScheduler::AbstractScheduler(unsigned int quanta){
		this->time_quanta = quanta;
		this->ready_list = {};
		this->running_process = nullptr;
		this->cpu_core = nullptr;
}

/**
 * @brief Constructor with no input, necessary for the feed class, which 
 * automatically creates schedulers
*/
AbstractScheduler::AbstractScheduler(){
		this->time_quanta = 0;
		this->ready_list = {};
		this->running_process = nullptr;
}

/**
 * @brief AbstractScheduler destructor
*/
AbstractScheduler::~AbstractScheduler(){
	delete this->running_process;
}

/**
 * @brief Exchange the current running context to the next one, according to the
 * 		Rate Monotonic algorithm
 * @returns 0: if not failed
 * 			-1: if failed
*/
int AbstractScheduler::swap_context(){
	if(this->ready_list.empty()){
		return -1;	// Error
	}

	// Save the context object
	if(this->running_process != nullptr){
		AbstractContext *running_context;
		running_context = this->get_cpu_core()->currentContext();
		this->running_process->set_context(running_context);
		this->add_to_ready(this->running_process);
	}

	// Pop next process from the ready list
	Process *next_to_run;
	next_to_run = this->ready_list.front();
	this->ready_list.erase(this->ready_list.begin());

	// Save process that will be put to run
	this->running_process = next_to_run;

	// Loads the next context
	AbstractContext *process_last_context;
	process_last_context = this->running_process->get_context();
	this->get_cpu_core()->setContext(process_last_context);
	
	return 0; // No error
}

/**
 * @brief Gets the time quanta the SO is setup to use
 * @returns time_quanta
*/
unsigned int AbstractScheduler::get_time_quanta(){
	return this->time_quanta;
}

/**
 * @brief Sets a new time quanta for the SO to use
 * @param quanta: Integer representing the time quanta in a time unit
 * @returns 0: if successfull
 * 			-1: if failed
*/
int AbstractScheduler::set_time_quanta(int quanta){
	this->time_quanta = quanta;

	return 0; // No error
}

/**
 * @brief Gets list of ready Process descriptor object has a list
 * @returns list of the Processes in thr ready state
*/
std::list<Process*> AbstractScheduler::get_ready_list(){
	return this->ready_list;
}

/**
 * @brief Sets a new list of ready Processes
 * 		ATENTION: This will erase the previos list!!
 * @param process_vec: Process descriptor object to be added as a list
 * @returns 0: if successfull
 * 			-1: if failed
*/
int AbstractScheduler::set_ready_list(std::list<Process*> process_vec){
	for(Process* pP : process_vec){
		// Ensures the list is sorted
		this->add_to_ready(pP);
	}

	return 0; // No error
}

/**
 * @brief Gets the currently running process
 * @returns Pointer to Process descriptor object of the currently running Process
*/
Process* AbstractScheduler::get_running_process(){
	return this->running_process;
}

/**
 * @brief Sets a given Process to run
 * @param process: Pointer to the Process descriptor object to be set to run
 * @returns 0: if successfull
 * 			-1: if failed
*/
int AbstractScheduler::set_running_process(Process* process){
	this->running_process = process;

	return 0; // No error
}

/**
 * @brief Gets all CPU registered
 * @return A list of the CPU descriptor object
*/
ProcessorCore* AbstractScheduler::get_cpu_core(){
	return this->cpu_core;
}

/**
 * @brief Sets a new list of CPUs
 * @param core_vec: CPUs descriptor object as a list
 * @returns 0: if successfull
 * 			-1: if failed
*/
int AbstractScheduler::set_cpu_core(ProcessorCore* core_vec){
	this->cpu_core = core_vec;

	return 0; // No error
}


/* RM Scheduler methods -----------------------------------------------------*/
/**
 * @brief Constructor with no input, necessary for the feed class, which 
 * automatically creates schedulers
*/
RMScheduler::RMScheduler(){
	this->time_quanta = 0;
	this->ready_list = {};
	this->running_process = nullptr;
	this->cpu_core = new ProcessorCore();
}

/**
 * @brief Exchange the current running context to the next one, according to the
 * 		Rate Monotonic algorithm
 * @returns 0: if not failed
 * 			-1: if failed
*/
int RMScheduler::swap_context(){
	if(this->ready_list.empty()){
		return -1;	// Error
	}

	// Save the context object
	if(this->running_process != nullptr){
		AbstractContext *running_context;
		running_context = this->get_cpu_core()->currentContext();
		this->running_process->set_context(running_context);
		if(this->running_process->get_state() != FINISHED){
			this->add_to_ready(this->running_process);
		} else  this->running_process->set_state(REMOVED);
	}

	// Pop next process from the ready list
	Process *next_to_run;
	next_to_run = this->ready_list.front();
	this->ready_list.erase(this->ready_list.begin());

	// Save process that will be put to run
	this->running_process = next_to_run;

	// Loads the next context
	AbstractContext *process_last_context;
	process_last_context = this->running_process->get_context();
	this->cpu_core->setContext(process_last_context);
	
	return 0; // No error
}

/**
 * @brief Adds a Process to the ready list in the appropriated position
 * @param process: The Process descriptor object to be added
 * @returns 0: if successfull
 * 			-1: if failed
*/
int RMScheduler::add_to_ready(Process* process){
	// Set ProcessState
	process->set_state(READY);
	
	// If this process is already on the registered, it's deadline is probably violated
	// Remove it to re-add in the right place
	this->ready_list.remove(process);
	if(this->running_process == process){
		this->set_running_process(nullptr);
	}


	std::list<Process*>::iterator iter = this->ready_list.begin();
	if(!this->ready_list.empty()){
		for (; iter != this->ready_list.end(); ++iter) {
			if(process->get_priority() > (*iter)->get_priority()){
				break;
			}
		}
	} 
	this->ready_list.insert(iter, process);


	return 0; // No error
}

/**
 * @brief Tests if the first process has higher priority as the running process
 * @returns false: if it has not higher priority
 * 			true: if it has
*/
bool RMScheduler::check_first_in_ready(){
	Process *first_in_ready = *(this->ready_list.begin());
	if(first_in_ready->get_priority() > this->running_process->get_priority()){
		return true;
	}
	return false;
}

int RMScheduler::remove_from_ready(Process* process){
	// for(Process *p: this->ready_list){
	std::list<Process*>::iterator iter = this->ready_list.begin();
	for(;iter != this->ready_list.end(); ++iter){
		if((*iter) == process){
			this->ready_list.erase(iter);
			return 1;
		}
	}

	return 0;
}

/**
 * @brief Gets the time quanta the SO is setup to use
 * @returns time_quanta
*/
unsigned int RMScheduler::get_time_quanta(){
	return this->time_quanta;
}

/**
 * @brief Sets a new time quanta for the SO to use
 * @param quanta: Integer representing the time quanta in a time unit
 * @returns 0: if successfull
 * 			-1: if failed
*/
int RMScheduler::set_time_quanta(int quanta){
	this->time_quanta = quanta;

	return 0; // No error
}

/**
 * @brief Gets list of ready Process descriptor object has a list
 * @returns list of the Processes in thr ready state
*/
std::list<Process*> RMScheduler::get_ready_list(){
	return this->ready_list;
}

/**
 *  @todo Add the option of adding many processes to the ready list at once
 * as a list or as a list, or array. Add this options to set_ready list to
*/
/**
 * @todo Clean redy list before saving new Processes in it when set_ready_list is used
*/

/**
 * @brief Sets a new list of ready Processes
 * 		ATENTION: This will erase the previos list!!
 * @param process_vec: Process descriptor object to be added as a list
 * @returns 0: if successfull
 * 			-1: if failed
*/
int RMScheduler::set_ready_list(std::list<Process*> process_vec){
	for(Process* pP : process_vec){
		// Ensures the list is sorted
		this->add_to_ready(pP);
	}

	return 0; // No error
}

/**
 * @brief Gets the currently running process
 * @returns Pointer to Process descriptor object of the currently running Process
*/
Process* RMScheduler::get_running_process(){
	return this->running_process;
}

/**
 * @brief Sets a given Process to run
 * @param process: Pointer to the Process descriptor object to be set to run
 * @returns 0: if successfull
 * 			-1: if failed
*/
int RMScheduler::set_running_process(Process* process){
	this->running_process = process;

	return 0; // No error
}

/**
 * @brief Gets all CPU registered
 * @return A list of the CPU descriptor object
*/
ProcessorCore* RMScheduler::get_cpu_core(){
	return this->cpu_core;
}

/**
 * @brief Sets a new list of CPUs
 * @param core_vec: CPUs descriptor object as a list
 * @returns 0: if successfull
 * 			-1: if failed
*/
int RMScheduler::set_cpu_core(ProcessorCore* core_vec){
	this->cpu_core = core_vec;

	return 0; // No error
}


/* EDF Scheduler methods -----------------------------------------------------*/
/**
 * @brief Constructor with no input, necessary for the feed class, which 
 * automatically creates schedulers
*/
EDFScheduler::EDFScheduler(){
	this->time_quanta = 0;
	this->ready_list = {};
	this->running_process = nullptr;
	this->cpu_core = new ProcessorCore();
}

/**
 * @brief Exchange the current running context to the next one, according to the
 * 		Rate Monotonic algorithm
 * @returns 0: if not failed
 * 			-1: if failed
*/
int EDFScheduler::swap_context(){
	if(this->ready_list.empty()){
		return -1;	// Error
	}

	// Save the context object
	if(this->running_process != nullptr){
		AbstractContext *running_context;
		running_context = this->get_cpu_core()->currentContext();
		this->running_process->set_context(running_context);
		if(this->running_process->get_state() != FINISHED){
			this->add_to_ready(this->running_process);
		} else  this->running_process->set_state(REMOVED);
	}

	// Pop next process from the ready list
	Process *next_to_run;
	next_to_run = this->ready_list.front();
	this->ready_list.erase(this->ready_list.begin());

	// Save process that will be put to run
	this->running_process = next_to_run;

	// Loads the next context
	AbstractContext *process_last_context;
	process_last_context = this->running_process->get_context();
	this->cpu_core->setContext(process_last_context);
	
	return 0; // No error
}

/**
 * @brief Adds a Process to the ready list in the appropriated position
 * @param process: The Process descriptor object to be added
 * @returns 0: if successfull
 * 			-1: if failed
*/
int EDFScheduler::add_to_ready(Process* process){
	// std::cout << "Chamado" << std::endl;
	// Set ProcessState
	process->set_state(READY);
	
	// If this process is already on the registered, it's deadline is probably violated
	// Remove it to re-add in the right place
	this->ready_list.remove(process);
	if(this->running_process == process){
		this->set_running_process(nullptr);
	}


	std::list<Process*>::iterator iter = this->ready_list.begin();
	if(!this->ready_list.empty()){
		for (; iter != this->ready_list.end(); ++iter) {
			int newbie_deadline = process->get_creation_time() + process->get_period();
			int old_deadline = (*iter)->get_creation_time() + (*iter)->get_period();
			// std::cout << "newbie_deadline: " << newbie_deadline << std::endl;
			// std::cout << "old_deadline: " << old_deadline << std::endl;
			if(newbie_deadline < old_deadline){
				break;
			}
		}
	} 
	this->ready_list.insert(iter, process);


	return 0; // No error
}

/**
 * @brief Tests if the first process has higher priority as the running process
 * @returns false: if it has not higher priority
 * 			true: if it has
*/
bool EDFScheduler::check_first_in_ready(){
	Process *first_in_ready = *(this->ready_list.begin());
	int ready_deadline = first_in_ready->get_creation_time() + first_in_ready->get_period();
	int running_deadline = this->running_process->get_creation_time() + this->running_process->get_period();
	if(ready_deadline < running_deadline){
		return true;
	}
	return false;
}

int EDFScheduler::remove_from_ready(Process* process){
	// for(Process *p: this->ready_list){
	std::list<Process*>::iterator iter = this->ready_list.begin();
	for(;iter != this->ready_list.end();++iter){
		if((*iter) == process){
			this->ready_list.erase(iter);
			return 1;
		}
	}

	return 0;
}

/**
 * @brief Gets the time quanta the SO is setup to use
 * @returns time_quanta
*/
unsigned int EDFScheduler::get_time_quanta(){
	return this->time_quanta;
}

/**
 * @brief Sets a new time quanta for the SO to use
 * @param quanta: Integer representing the time quanta in a time unit
 * @returns 0: if successfull
 * 			-1: if failed
*/
int EDFScheduler::set_time_quanta(int quanta){
	this->time_quanta = quanta;

	return 0; // No error
}

/**
 * @brief Gets list of ready Process descriptor object has a list
 * @returns list of the Processes in thr ready state
*/
std::list<Process*> EDFScheduler::get_ready_list(){
	return this->ready_list;
}

/**
 * @brief Sets a new list of ready Processes
 * 		ATENTION: This will erase the previos list!!
 * @param process_vec: Process descriptor object to be added as a list
 * @returns 0: if successfull
 * 			-1: if failed
*/
int EDFScheduler::set_ready_list(std::list<Process*> process_vec){
	for(Process* pP : process_vec){
		// Ensures the list is sorted
		this->add_to_ready(pP);
	}

	return 0; // No error
}

/**
 * @brief Gets the currently running process
 * @returns Pointer to Process descriptor object of the currently running Process
*/
Process* EDFScheduler::get_running_process(){
	return this->running_process;
}

/**
 * @brief Sets a given Process to run
 * @param process: Pointer to the Process descriptor object to be set to run
 * @returns 0: if successfull
 * 			-1: if failed
*/
int EDFScheduler::set_running_process(Process* process){
	this->running_process = process;

	return 0; // No error
}

/**
 * @brief Gets all CPU registered
 * @return A list of the CPU descriptor object
*/
ProcessorCore* EDFScheduler::get_cpu_core(){
	return this->cpu_core;
}

/**
 * @brief Sets a new list of CPUs
 * @param core_vec: CPUs descriptor object as a list
 * @returns 0: if successfull
 * 			-1: if failed
*/
int EDFScheduler::set_cpu_core(ProcessorCore* core_vec){
	this->cpu_core = core_vec;

	return 0; // No error
}