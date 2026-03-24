#include <bits/stdc++.h>
using namespace std;
class NQueens
{
public:
    int n;
    vector<vector<int>> board;
    vector<bool> col, diag1, diag2;
    NQueens(int n)
    {
        this->n = n;
        board.resize(n, vector<int>(n, 0));

        col.resize(n, false);
        diag1.resize(2 * n - 1, false);
        diag2.resize(2 * n - 1, false);
    }
    void printSolution()
    {
        cout << "\nSolution:\n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
    }
    bool solve(int row)
    {
        if (row == n)
        {
            printSolution();
            return true;
        }
        for (int c = 0; c < n; c++)
        {
            if (!col[c] && !diag1[row + c] && !diag2[row - c + n - 1])
            {
                board[row][c] = 1;
                col[c] = diag1[row + c] = diag2[row - c + n - 1] = true;
                if (solve(row + 1))
                    return true;
                board[row][c] = 0;
                col[c] = diag1[row + c] = diag2[row - c + n - 1] = false;
            }
        }
        return false;
    }
};

int main()
{
    int n;
    cout << "Enter value of N: ";
    cin >> n;
    NQueens obj(n);
    if (!obj.solve(0))
        cout << "No solution exists\n";
    return 0;
}