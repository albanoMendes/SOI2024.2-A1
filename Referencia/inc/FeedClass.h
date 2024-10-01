#ifndef _FEEDCLASS_H
#define _FEEDCLASS_H


#include <list>
#include "SchedulerClass.h"
#include "process.h"

/**
 * @defgroup Scheduling_rules
*/
#define RMSCHEDULING	0
#define EDFSCHEDULING	1


/**
 * @brief Class responsable to feed new processes to the Scheduler
*/
class Feed{
	public:
		Feed(std::list<Process*> p_vec, int rule);
		int step_time();
		unsigned int get_time();
		int set_time(int t);
		unsigned int get_number_of_swaps();
		int set_number_of_swaps(unsigned int number);
		std::list<Process*> get_processes();
		int set_processes(std::list<Process*> p_vec);
		AbstractScheduler* get_scheduler();
		int set_scheduler(AbstractScheduler *s);

	private:
		unsigned int time, number_of_swaps = 0;
		std::list<Process*> processes;
		AbstractScheduler *scheduler;
		RMScheduler rm_scheduler;
		EDFScheduler edf_scheduler;
};

#endif