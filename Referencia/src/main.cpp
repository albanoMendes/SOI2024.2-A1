#include <iostream>
#include "FileClass.h"
#include "FeedClass.h"

using namespace std;

/* Program entry point -------------------------------------------------------*/
int main(int argc, char* argv[]){
	// Creates objects
	File file;
	file.read_file();
	Feed rm_feed(file.get_processes(),RMSCHEDULING);

	// Prints diagram header
	cout << "\n\nESCALONAMENTO COM RM\n";
	cout << "Tempo\t";
	int i = 0;
	for(Process* p:rm_feed.get_processes()){
		cout << " P" << ++i << " ";
	}
	cout << endl;

	// Runs
	for(int i = 0;i <= 30;i++){
		rm_feed.step_time();
		cout << rm_feed.get_time()-1 << "-" << rm_feed.get_time();
		cout << "\t";
		for(Process *p:rm_feed.get_processes()){
			switch(p->get_state()){
				case READY:
					cout << " -- ";
					break;
				case EXECUTING:
				case FINISHED:
					cout << " ## ";
					break;
				case CREATED:
				case REMOVED:
					cout << "    ";
					break;
			}
		}
		cout << endl;
	}
	cout << endl;
	cout << "Deadlines missed:" << endl;
	for(Process* p:rm_feed.get_processes()){
		cout << " P" << ++i << " ";
	}
	cout << endl;
	for(Process* p:rm_feed.get_processes()){
		cout << "  " << p->get_miss_deadline() << " ";
	}
	cout << endl;
	cout << "Number of context swaps: ";
	cout << rm_feed.get_number_of_swaps() << endl;
	cout << "Time waited by each process:" << endl;
	for(Process* p:rm_feed.get_processes()){
		cout << " P" << ++i << " ";
	}
	cout << endl;
	for(Process* p:rm_feed.get_processes()){
		cout << "  " << p->get_waited_time() << " ";
	}
	cout << endl;
	cout << "Mean turnaround Time for each process:" << endl;
	for(Process* p:rm_feed.get_processes()){
		cout << " P" << ++i << " ";
	}
	cout << endl;
	for(Process* p:rm_feed.get_processes()){
		cout << "  " << p->get_mean_turnaround_time() << " ";
	}
	cout << endl;

	
	cout << endl;
	cout << endl;

	File file2;
	file2.read_file();
	Feed edf_feed(file2.get_processes(),EDFSCHEDULING);

	// Prints diagram header
	cout << "\n\nESCALONAMENTO COM EDF\n";
	cout << "Tempo\t";
	int j = 0;
	for(Process* p:edf_feed.get_processes()){
		cout << " P" << ++j << " ";
	}
	cout << endl;

	// Runs
	for(int i = 0;i <= 30;i++){
		edf_feed.step_time();
		cout << edf_feed.get_time()-1 << "-" << edf_feed.get_time();
		cout << "\t";
		for(Process *p:edf_feed.get_processes()){
			switch(p->get_state()){
				case READY:
					cout << " -- ";
					break;
				case EXECUTING:
				case FINISHED:
					cout << " ## ";
					break;
				case CREATED:
				case REMOVED:
					cout << "    ";
					break;
			}
		}
		cout << endl;
	}
	cout << endl;
	cout << "Deadlines missed:" << endl;
	for(Process* p:edf_feed.get_processes()){
		cout << " P" << ++i << " ";
	}
	cout << endl;
	for(Process* p:edf_feed.get_processes()){
		cout << "  " << p->get_miss_deadline() << " ";
	}
	cout << endl;
	cout << "Number of context swaps: ";
	cout << edf_feed.get_number_of_swaps() << endl;
	cout << "Time waited by each process:" << endl;
	for(Process* p:edf_feed.get_processes()){
		cout << " P" << ++i << " ";
	}
	cout << endl;
	for(Process* p:edf_feed.get_processes()){
		cout << "  " << p->get_waited_time() << " ";
	}
	cout << endl;
	cout << "Mean turnaround Time for each process:" << endl;
	for(Process* p:edf_feed.get_processes()){
		cout << " P" << ++i << " ";
	}
	cout << endl;
	for(Process* p:edf_feed.get_processes()){
		cout << "  " << p->get_mean_turnaround_time() << " ";
	}
	cout << endl;
	

	return 0;
}
