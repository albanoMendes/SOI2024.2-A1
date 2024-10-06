#ifndef FEED_H
#define FEED_H

#include <list>
#include "AbstractScheduler.h"

class Feed {
public:
    std::list<Job*> processes;
    AbstractScheduler* scheduler;

    Feed(AbstractScheduler* sched);

    void sleep(int time);
    std::list<Job*> running();
};

#endif
