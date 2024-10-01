#include <iostream>
#include "FileClass.h"
#include "INE5412Context.hpp"

/* File class methods implementation -----------------------------------------*/
File::File() {
	myfile.open("entrada.txt");
	if (!myfile.is_open()) {
		std::cout << "Erro ao abrir o arquivo!\n";
	}
}

File::~File() {
	// std::list<Process*>::iterator iter = processes.begin();
	// for(int i = 0; i < processes.size() ; i++) {
	for(Process *process: this->processes) {
		// std::advance(iter,i);
		Process *p = process;
		delete p;
	}
}

void File::print_processes_params() {
	std::list<Process *>::iterator iter = processes.begin();

	// for(iter; iter < processes.end(); iter++) {
	// 	Process *p = *iter;
	// 	std::cout << *p;
	// }
}

void File::read_file() {
	int a, b, c, d, e;
	
	if (!myfile.is_open()) {
		std::cout << "Arquivo não está aberto!" << std::endl;
	}
	
	while (myfile >> a >> b >> c >> d >> e) {
		Process *p = new Process(a, b, c, e);
		p->set_context(new INE5412Context());
		processes.push_back(p);
	}

	std::cout << "Quantidade de processos lidos do arquivo: " << processes.size() << std::endl;
}

std::list<Process*> File::get_processes(){
	return this->processes;
}