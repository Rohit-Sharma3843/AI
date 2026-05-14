#include <iostream>
#include <vector>
using namespace std;
void selection_sort(vector<int> v)
{
    for (int i = 0; i < v.size() - 1; i++)
    {
        int min = i;
        for (int j = i; j < v.size(); j++)
        {
            if (v[min] > v[j])
            {
                min = j;
            }
        }
        swap(v[min], v[i]);
    }
    for (auto i : v)
    {
        cout << i << " ";
    }
}
int main()
{
    vector<int> v = {4, 9, -12, 47, 20, 36, 72, -9, 12, 48, 90, 186, 62, -114};
    selection_sort(v);
    return 0;
}