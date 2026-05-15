#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Job
{
public:
    string name;
    int deadline;
    int profit;
};
class Compare
{
public:
    bool operator()(Job j1, Job j2)
    {
        return j1.profit > j2.profit;
    }
};
int main()
{
    int n;
    cout << "Number of jobs : ";
    cin >> n;
    vector<Job> jobs(n);
    cout << "Enter jobs : ";
    string nm;
    int dl, pr;
    int maxdd = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> nm >> dl >> pr;
        Job j;
        j.name = nm;
        j.deadline = dl,
        j.profit = pr;
        jobs[i] = j;
        maxdd = max(maxdd, dl);
    }
    sort(jobs.begin(), jobs.end(), Compare());
    vector<string> slots(maxdd + 1, "_");
    int profit = 0;
    for (auto i : jobs)
    {
        for (int j = i.deadline; j >= 1; j--)
        {
            if (slots[j] == "_")
            {
                slots[j] = i.name;
                profit += i.profit;
                break;
            }
        }
    }
    for (int i = 1; i <= maxdd; i++)
    {
        if (slots[i] != "_")
        {
            cout << slots[i] << " ";
        }
    }
    cout << endl
         << endl;
    cout << "Profit : " << profit << endl;
    return 0;
}