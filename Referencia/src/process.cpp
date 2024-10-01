#include "process.h"

Process::Process(int creation_time, int duration, int period, int priority)
{
    this->creation_time = creation_time;
    this->duration = duration;
    this->period = period;
    this->priority = priority;
    this->context = nullptr;
    this->executed_time = 0;
}

Process::~Process()
{
    delete context;
}

int Process::get_creation_time()
{
    return this->creation_time;
}

int Process::get_duration()
{
    return this->duration;
}

int Process::get_priority()
{
    return this->priority;
}

int Process::get_period()
{
    return this->period;
}

int Process::get_executed_time()
{
    return this->executed_time;
}

int Process::get_waited_time(){
    return this->waited_time;
}

double Process::get_mean_turnaround_time(){
    return this->mean_turnaround_time;
}

unsigned int Process::get_miss_deadline(){
    return this->missed_deadline;
}

ProcessState Process::get_state()
{
    return this->state;
}

AbstractContext *Process::get_context()
{
    return this->context;
}

void Process::set_creation_time(int creation_time)
{
    this->creation_time = creation_time;
}

void Process::set_duration(int duration)
{
    this->duration = duration;
}

void Process::set_priority(int priority)
{
    this->priority = priority;
}

void Process::set_period(int period)
{
    this->period = period;
}

void Process::set_miss_deadline(unsigned int deadline){
    this->missed_deadline = deadline;
}

void Process::set_context(AbstractContext *context)
{
    this->context = context;
}

void Process::set_state(ProcessState state)
{
    this->state = state;
}

void Process::set_executed_time(int exec_time){
    this->executed_time = exec_time;
}

void Process::set_waited_time(int wait_time){
    this->waited_time = wait_time;
}

void Process::increment_executed_time(){

    this->executed_time++;
    if (this->executed_time == this->duration) {
        this->state = FINISHED;
    } else {
        this->state = EXECUTING;
    }
}

void Process::increment_waited_time(){
    this->waited_time++;
}

void Process::update_mean_turnaround_time(int turnaround_time){
    this->ending_counts++;
    this->mean_turnaround_time = (turnaround_time + (this->ending_counts-1)*this->mean_turnaround_time)/this->ending_counts;
}

void Process::miss_deadline(){
    this->missed_deadline++;
}
