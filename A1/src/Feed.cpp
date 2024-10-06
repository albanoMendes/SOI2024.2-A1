#include "Feed.h"
#include <chrono>
#include <thread>

Feed::Feed(AbstractScheduler* sched) {
    this->scheduler = sched;
}

void Feed::sleep(int time) {
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

std::list<Job*> Feed::running() {
    return scheduler->ready_list;
}
