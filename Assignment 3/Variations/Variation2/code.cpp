#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Job
{
    char id;
    int deadline;
    int profit;
};
bool cmp(Job a, Job b)
{
    return a.profit > b.profit;
}
int main()
{
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;
    vector<Job> jobs(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Job ID Deadline Profit: ";
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;
    }
    sort(jobs.begin(), jobs.end(), cmp);
    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
    {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }
    vector<char> slot(maxDeadline + 1, '0');
    int totalProfit = 0;
    cout << "Selected Jobs: ";
    for (int i = 0; i < n; i++)
    {
        for (int j = jobs[i].deadline; j > 0; j--)
        {
            if (slot[j] == '0')
            {
                slot[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                cout << jobs[i].id << " ";
                break;
            }
        }
    }
    cout << endl;
    cout << "Total Profit: " << totalProfit << endl;
    return 0;
}