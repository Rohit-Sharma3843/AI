#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int n;
    cout << "Enter number of packages: ";
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter weight of package " << i + 1 << ": ";
        cin >> arr[i];
    }
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
    cout << "Packages sorted from lightest to heaviest:\n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}