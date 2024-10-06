#ifndef JOB_H
#define JOB_H

#include <iostream>

class AbstractContext; // Declaração antecipada

class Job {
public:
    int id;
    int startTime;
    int endTime;
    int profit;
    AbstractContext* last_context; // Ponteiro para o último contexto

    Job(int id, int startTime, int endTime, int profit) {
        this->id = id;
        this->startTime = startTime;
        this->endTime = endTime;
        this->profit = profit;
        this->last_context = nullptr; // Contexto inicial é nulo
    }
};

#endif