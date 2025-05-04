/*Consider the scheduling problem. n tasks to be scheduled on single processor. Let t1, ...,tn be durations required to execute on single processor is known. The tasks can be executed in any order but one task at a time. Design a greedy algorithm for this problem and find a schedule that minimizes the total time spent by all the tasks in the system. (The time spent by one is the sum of the waiting time of task and the time spent on its execution.)*/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    vector<int> tasks = {3, 1, 2};
    sort(tasks.begin(), tasks.end());
    int curr = 0;
    int total = 0;
    for (int i = 0; i < tasks.size(); i++)
    {
        curr += tasks[i];
        total += curr;
    }
    cout << "Minimum total time spent by all tasks " << total << "\n";
    return 0;
}
