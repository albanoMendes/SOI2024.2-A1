#include "AbstractScheduler.h"
#include <algorithm>

AbstractScheduler::AbstractScheduler() {
    running_process = nullptr;
    cpuCore = new ProcessCore();
}

int AbstractScheduler::jobScheduling(std::vector<int>& startTime, std::vector<int>& endTime, std::vector<int>& profit) {
    int n = startTime.size();
    std::vector<int> dp(n, 0);

    std::vector<std::tuple<int, int, int>> jobs;
    for (int i = 0; i < n; ++i) {
        jobs.push_back({endTime[i], startTime[i], profit[i]});
    }

    std::sort(jobs.begin(), jobs.end());

    dp[0] = std::get<2>(jobs[0]);

    for (int i = 1; i < n; ++i) {
        int currentProfit = std::get<2>(jobs[i]);
        int lastNonConflict = -1;

        for (int j = i - 1; j >= 0; --j) {
            if (std::get<1>(jobs[j]) <= std::get<0>(jobs[i])) {
                lastNonConflict = j;
                break;
            }
        }

        if (lastNonConflict != -1) {
            currentProfit += dp[lastNonConflict];
        }

        dp[i] = std::max(dp[i - 1], currentProfit);
    }

    return dp[n - 1];
}

bool AbstractScheduler::executar(Job* run_p) {
    cpuCore->setContext(run_p->last_context);
    running_process = run_p;
    return true;
}
