#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Patient
{
    char id;
    int deadline;
    int duration;
};
bool cmp(Patient a, Patient b)
{
    return a.deadline < b.deadline;
}
int main()
{
    int n;
    cout << "Enter number of patients: ";
    cin >> n;
    vector<Patient> p(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Patient ID Deadline Duration: ";
        cin >> p[i].id >> p[i].deadline >> p[i].duration;
    }
    sort(p.begin(), p.end(), cmp);
    int currentTime = 0, count = 0;
    cout << "Scheduled Patients:\n";
    for (int i = 0; i < n; i++)
    {
        if (currentTime + p[i].duration <= p[i].deadline)
        {
            cout << p[i].id << " ";
            currentTime += p[i].duration;
            count++;
        }
    }
    cout << endl;
    cout << "Total Patients Completed: " << count << endl;
    cout << "Total Time Used: " << currentTime << endl;
    return 0;
}