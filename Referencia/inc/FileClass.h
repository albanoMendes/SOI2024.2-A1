#ifndef _FILECLASS_H
#define _FILECLASS_H

#include <list>
#include <fstream>
#include "process.h"


/**
 * @brief Class implementing file reading and interpretation
*/
class File{
	public:
		File();	
		void read_file();
		void print_processes_params();
		~File();
		std::list<Process*> get_processes();

	private:
		std::ifstream myfile; 
		std::list<Process*> processes;
};

#endif