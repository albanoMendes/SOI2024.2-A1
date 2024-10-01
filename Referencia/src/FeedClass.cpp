#include "FeedClass.h"
#include <iostream>

/**
 * @brief Constructor for the Feed class
 * @param p_vec: Process list
 * @param rule: Desired Scheduler rule from Scheduling_rules defgroup
 * 			RMSCHEDULING: Rate Monotonic
 * 			EDFSCHEDULING: Earliest Deadline First
*/
Feed::Feed(std::list<Process*> p_vec, int rule){
	this->time = 0;
	this->processes = p_vec;
	switch(rule){
		case RMSCHEDULING: this->scheduler = (AbstractScheduler*) &rm_scheduler; break;
		case EDFSCHEDULING:this->scheduler = (AbstractScheduler*) &edf_scheduler; break;
	}
	// this->scheduler->add_cpu_core();
	this->scheduler->set_time_quanta(1);
}

int Feed::step_time(){
	int retval = 0;
	// Feeds newer processes to the scheduler
	for(Process *p: this->processes){
		if(p->get_creation_time() == this->time ||
			p->get_creation_time()+p->get_period() == this->time)
		{		
			// 	Check if the new process is the one running
			Process *running_process = this->scheduler->get_running_process();
			if(running_process != nullptr){
				if(p == running_process){
					if(running_process->get_state() != FINISHED){
						running_process->miss_deadline();
					} else if (running_process->get_state() == FINISHED){
						running_process->update_mean_turnaround_time(
							this->time - running_process->get_creation_time()
							);
					}
				}

			}
			
			// Checks if the new process is in the ready list
			if(this->scheduler->remove_from_ready(p)){
				p->miss_deadline();
			}
			

			// Setup the new process
			p->set_creation_time(this->time); // Creates the periodicity
			p->set_executed_time(0); // Creates the periodicity
			

			this->scheduler->add_to_ready(p);
		}
	}

	// Checks the necessity of swaping the context
	Process *process = this->scheduler->get_running_process();
	if(process == nullptr){
		retval = this->scheduler->swap_context();
		this->number_of_swaps++;
	} else if(process->get_state() == FINISHED){
		process->update_mean_turnaround_time(this->time-process->get_creation_time());
		retval = this->scheduler->swap_context();
		this->number_of_swaps++;
	} else if(this->scheduler->check_first_in_ready()){
		retval = this->scheduler->swap_context();
		this->number_of_swaps++;
	}	
			
	
	// Steps time in the program
	process = this->scheduler->get_running_process();
	process->increment_executed_time();
	for(Process* p:this->get_scheduler()->get_ready_list()){
		p->increment_waited_time();
	}

	this->time++;

	return retval;
}

unsigned int Feed::get_time(){
	return this->time;
}

int Feed::set_time(int t){
	this->time = t;

	return 0;	// No error
}

unsigned int Feed::get_number_of_swaps(){
	return this->number_of_swaps;
}

int Feed::set_number_of_swaps(unsigned int number){
	this->number_of_swaps = number;

	return 0; // No error
}

std::list<Process*> Feed::get_processes(){
	return this->processes;
}

int Feed::set_processes(std::list<Process*> p_vec){
	this->processes = p_vec;

	return 0;	// No error
}

AbstractScheduler* Feed::get_scheduler(){
	return (AbstractScheduler*) this->scheduler;
}

int Feed::set_scheduler(AbstractScheduler *s){
	this->scheduler = (AbstractScheduler*) s;

	return 0;	//No error
}

