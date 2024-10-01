#ifndef _SCHEDULER_CLASS_H
#define _SCHEDULER_CLASS_H

#include <list>
#include "process.h"
#include "ProcessorCore.hpp"

/**
 * @brief Defines basic structure for a Scheduler class
*/
class AbstractScheduler {
	public:
		AbstractScheduler(unsigned int quanta);
		AbstractScheduler();
		~AbstractScheduler();
		virtual int add_to_ready(Process* process) { return 0; };
		virtual int swap_context();
		virtual bool check_first_in_ready() { return false;};
		virtual int remove_from_ready(Process* process) { return 0;};
		virtual unsigned int get_time_quanta(void);
		virtual int set_time_quanta(int quanta);
		virtual std::list<Process*> get_ready_list(void);
		virtual int set_ready_list(std::list<Process*> process_vec);
		virtual Process* get_running_process(void);
		virtual int set_running_process(Process* process);
		virtual ProcessorCore* get_cpu_core(void);
		virtual int set_cpu_core(ProcessorCore* core_vec);

	private:
		unsigned int time_quanta;
		std::list<Process*> ready_list;
		Process* running_process;
		ProcessorCore* cpu_core;
};

/**
 * @brief Declares all functions of a class to describe a Rate Monotonic Scheduler
*/
class RMScheduler : public AbstractScheduler {
	public:
		RMScheduler(unsigned int quanta) : AbstractScheduler(quanta) {};
		RMScheduler();
		int add_to_ready(Process* process) override;
		int swap_context() override;
		bool check_first_in_ready() override;
		int remove_from_ready(Process* process) override;
		unsigned int get_time_quanta(void) override;
		int set_time_quanta(int quanta) override;
		std::list<Process*> get_ready_list(void) override;
		int set_ready_list(std::list<Process*> process_vec) override;
		Process* get_running_process(void) override;
		int set_running_process(Process* process) override;
		ProcessorCore* get_cpu_core(void) override;
		int set_cpu_core(ProcessorCore* core_vec) override;

	private:
		unsigned int time_quanta;
		std::list<Process*> ready_list;
		Process* running_process;
		ProcessorCore* cpu_core;
};

/**
 * @brief Declares all functions of a class to describe a Earliest Deadline First Scheduler
*/
class EDFScheduler : public AbstractScheduler {
	public:
		EDFScheduler(unsigned int quanta) : AbstractScheduler(quanta) {};
		EDFScheduler();
		int add_to_ready(Process* process) override;
		int swap_context() override;
		bool check_first_in_ready() override;
		int remove_from_ready(Process* process) override;
		unsigned int get_time_quanta(void) override;
		int set_time_quanta(int quanta) override;
		std::list<Process*> get_ready_list(void) override;
		int set_ready_list(std::list<Process*> process_vec) override;
		Process* get_running_process(void) override;
		int set_running_process(Process* process) override;
		ProcessorCore* get_cpu_core(void) override;
		int set_cpu_core(ProcessorCore* core_vec) override;

	private:
		unsigned int time_quanta;
		std::list<Process*> ready_list;
		Process* running_process;
		ProcessorCore* cpu_core;
};

#endif