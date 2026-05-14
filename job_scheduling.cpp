// CPU Scheduling Algorithms: FCFS, SJF (Preemptive), Priority
//(Non - Preemptive) and Round Robin(Preemptive).
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
class Job
{
public:
    string name;
    int arrival;
    int burst;
    int turnaround;
    int completion;
    int wait;
    int priority;
    int remaining;

    Job(string name, int arrival, int burst, int priority)
    {
        this->name = name;
        this->arrival = arrival;
        this->burst = burst;
        this->priority = priority;
        this->turnaround = -1;
        this->completion = -1;
        this->wait = -1;
        this->remaining = burst;
    }
};
class Compare1
{
public:
    bool operator()(Job j1, Job j2)
    {
        return j1.arrival < j2.arrival;
    }
};
class Compare2
{
public:
    bool operator()(Job j1, Job j2)
    {
        return j1.remaining > j2.remaining;
    }
};
class Compare3
{
public:
    bool operator()(Job j1, Job j2)
    {
        return j1.priority > j2.priority;
    }
};
class JobList
{
    int number;
    vector<Job> list;

public:
    JobList()
    {
        int n;
        cout << "Enter the number of jobs : ";
        cin >> n;
        this->number = n;
        string name;
        int arrival, burst, priority;
        for (int i = 0; i < number; i++)
        {
            cout << "Enter the name of job " << i + 1 << " : ";
            cin >> name;
            cout << "Enter the arrival time of job " << name << " : ";
            cin >> arrival;
            cout << "Enter the burst time of job " << name << " : ";
            cin >> burst;
            cout << "Enter the priority of job " << name << " : ";
            cin >> priority;
            Job j(name, arrival, burst, priority);
            list.push_back(j);
        }
    }
    void fcfs()
    {
        sort(list.begin(), list.end(), Compare1());
        cout << "FCFS scheduling : ";
        for (int i = 0; i < list.size(); i++)
        {
            cout << list[i].name << " ";
        }
    }
    void sjf()
    {
        int time = 0;
        int completed = 0;
        priority_queue<Job, vector<Job>, Compare2> pq;
        vector<Job> done;
        while (completed < number)
        {
            for (int i = 0; i < list.size(); i++)
            {
                if (list[i].arrival == time)
                {
                    pq.push(list[i]);
                }
            }
            auto i = pq.top();
            pq.pop();
            i.remaining -= 1;
            time += 1;
            if (i.remaining == 0)
            {
                completed += 1;
                i.completion = time;
                i.turnaround = time - i.arrival;
                i.wait = i.turnaround - i.burst;
                done.push_back(i);
            }
            else
            {
                pq.push(i);
            }
        }
        sort(done.begin(), done.end(), Compare1());
        for (auto i : done)
        {
            cout << i.name << "  " << i.arrival << "  " << i.burst << "  " << i.completion << "  " << i.wait << "  " << i.turnaround << endl;
        }
    }
    void priority_scheduling()
    {
        sort(list.begin(), list.end(), Compare3());
        for (auto i : list)
        {
            cout << i.name << " ";
        }
    }
    void round_robin(int tq)
    {
        sort(list.begin(), list.end(), Compare1());
        queue<int> q;
        vector<bool> added(number, false);
        int completed = 0;
        added[0] = true;
        q.push(0);
        int time = list[0].arrival;
        while (completed < number)
        {
            if (q.empty())
            {
                time += 1;
                for (int j = 0; j < list.size(); j++)
                {
                    if (!added[j] && list[j].arrival <= time)
                    {
                        q.push(j);
                        added[j] = true;
                    }
                }
                continue;
            }
            auto i = q.front();
            q.pop();
            int executed = min(list[i].remaining, tq);
            list[i].remaining -= executed;
            time += executed;
            for (int j = 0; j < list.size(); j++)
            {
                if (!added[j] && list[j].arrival <= time)
                {
                    q.push(j);
                    added[j] = true;
                }
            }
            if (list[i].remaining != 0)
            {
                q.push(i);
            }
            else
            {
                completed++;
                list[i].remaining = 0;
                list[i].completion = time;
                list[i].turnaround = time - list[i].arrival;
                list[i].wait = list[i].turnaround - list[i].burst;
            }
        }
        for (auto i : list)
        {
            cout << i.name << "  " << i.arrival << "  " << i.burst << "  " << i.completion << "  " << i.wait << "  " << i.turnaround << endl;
        }
    }
};
int main()
{
    JobList j1;
    j1.sjf();
    cout << endl;
    j1.priority_scheduling();
    cout << endl
         << endl;
    j1.round_robin(2);
    return 0;
}