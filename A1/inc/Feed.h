#ifndef _FEED_H
#define _FEED_H

#include "Job.h"
#include "AbstractScheduler.h"

class Feed {
	private:
    std::list<Job*> processes;
    AbstractScheduler scheduler;
	public:
    ~Feed();
		void sleep(int time_);
    std::list<Job*> running()
		
};
#endif

