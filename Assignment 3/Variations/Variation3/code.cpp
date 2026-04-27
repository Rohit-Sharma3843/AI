#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
struct Item
{
    int weight;
    int value;
    double ratio;
};
bool cmp(Item a, Item b)
{
    return a.ratio > b.ratio;
}
int main()
{
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;
    vector<Item> items(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter weight and value: ";
        cin >> items[i].weight >> items[i].value;
        items[i].ratio = (double)items[i].value / items[i].weight;
    }
    cout << "Enter knapsack capacity: ";
    cin >> capacity;
    sort(items.begin(), items.end(), cmp);
    double totalValue = 0;
    cout << "Selected Items:\n";
    for (int i = 0; i < n; i++)
    {
        if (capacity == 0)
            break;
        if (items[i].weight <= capacity)
        {
            capacity -= items[i].weight;
            totalValue += items[i].value;
            cout << "Take full item (W=" << items[i].weight << ", V=" << items[i].value << ")\n";
        }
        else
        {
            double fraction = (double)capacity / items[i].weight;
            totalValue += items[i].value * fraction;
            cout << "Take " << fixed << setprecision(2) << fraction * 100 << "% of item (W=" << items[i].weight << ", V=" << items[i].value << ")\n";
            capacity = 0;
        }
    }
    cout << "Maximum Value: " << fixed << setprecision(2) << totalValue << endl;
    return 0;
}