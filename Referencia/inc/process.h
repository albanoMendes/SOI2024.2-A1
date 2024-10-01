#ifndef _PROCESS_H
#define _PROCESS_H

#include "AbstractContext.hpp"

enum ProcessState {CREATED, READY, EXECUTING, FINISHED, REMOVED};

class Process
{

private:
    int creation_time, duration, priority, period;
    int executed_time = 0, waited_time = 0;
    double mean_turnaround_time = 0;
    int ending_counts = 0;
    unsigned int missed_deadline = 0;
    ProcessState state = CREATED;
    AbstractContext *context;

public:
    Process(int creation_time, int duration, int period, int priority);//, AbstractContext *context);

    ~Process();

    int get_creation_time();

    int get_duration();

    int get_priority();

    int get_period();

    int get_executed_time();

    int get_waited_time();

    double get_mean_turnaround_time();

    unsigned int get_miss_deadline();

    ProcessState get_state();

    AbstractContext *get_context();

    void set_creation_time(int creation_time);

    void set_duration(int duration);

    void set_priority(int priority);

    void set_period(int period);

    void set_executed_time(int exec_time);

    void set_waited_time(int wait_time);

    void set_miss_deadline(unsigned int deadline);

    void set_context(AbstractContext *context);

    void set_state(ProcessState state);

    void increment_executed_time();

    void increment_waited_time();

    void update_mean_turnaround_time(int turnaround_time);

    void miss_deadline();

};

#endif