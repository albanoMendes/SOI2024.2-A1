#ifndef _ABSTRACTSCHEDULER_CLASS_H
#define _ABSTRACTSCHEDULER_CLASS_H

#include <list>
#include "ProcessCore.h"
#include "Job.h"

class AbstractScheduler {
	private:
    std::list<Job*> ready_list;
    Job *running_process;
    ProcessorCore *cpuCore;
	public:
		~AbstractScheduler();
		int jobScheduling(list<int*> startTime, list<int*> endTime, list<int*> profit)
		bool executar(Job *run_p)
};

#endif