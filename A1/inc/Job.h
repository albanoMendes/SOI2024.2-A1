#ifndef _JOB_H
#define _JOB_H

#include "AbstractContext.hpp"

class Job {
	private:
    	int  id;
      int startTime;
    	int endTime;
      int profit;
      AbstractContext *context;
	public:
    Job(int id, int startTime, int endTime, int profit, AbstractContext *context);//, AbstractContext *context);

    ~Job();

    void setId(int id_);
		void setStartTime(int startTime_);
		void setEndTime(uint64_t endTime_);
    void setProfit(int profit_);
		void setContext(AbstractContext *context_);
    int getId();
		int getStartTime();
    int getEndTime();
    int getProfit();
    AbstractContext* getContext();
};
#endif