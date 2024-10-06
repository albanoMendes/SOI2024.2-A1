#ifndef ABSTRACTSCHEDULER_H
#define ABSTRACTSCHEDULER_H

#include <list>
#include <vector>
#include "Job.h"
#include "ProcessCore.h"

class AbstractScheduler {
public:
    std::list<Job*> ready_list;
    Job* running_process;
    ProcessCore* cpuCore;

    AbstractScheduler();

    int jobScheduling(std::vector<int>& startTime, std::vector<int>& endTime, std::vector<int>& profit);
    bool executar(Job* run_p);
};

#endif
