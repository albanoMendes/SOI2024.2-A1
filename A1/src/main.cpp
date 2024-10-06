#include <iostream>
#include <fstream>
#include <vector>
#include "Job.h"
#include "AbstractScheduler.h"
#include "Feed.h"

void readJobsFromFile(const std::string& filename, std::vector<int>& startTimes, std::vector<int>& endTimes, std::vector<int>& profits, std::vector<int>& ids) {
    std::ifstream infile(filename);
    
    if (!infile) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return;
    }

    int startTime, endTime, profit, id, redundant;
    while (infile >> redundant >> startTime >> endTime >> profit >> id) {
        startTimes.push_back(startTime);
        endTimes.push_back(endTime);
        profits.push_back(profit);
        ids.push_back(id);
    }

    infile.close();
}

int main() {
    // Vetores para armazenar os dados lidos do arquivo
    std::vector<int> startTimes;
    std::vector<int> endTimes;
    std::vector<int> profits;
    std::vector<int> ids;

    // Ler o arquivo de entrada
    std::string filename = "entrada.txt";
    readJobsFromFile(filename, startTimes, endTimes, profits, ids);

    // Criar o escalonador
    AbstractScheduler scheduler;

    // Realizar o escalonamento com base nos tempos e lucros lidos do arquivo
    int maxProfit = scheduler.jobScheduling(startTimes, endTimes, profits);

    // Exibir o lucro máximo
    std::cout << "Lucro máximo: " << maxProfit << std::endl;

    return 0;
}
