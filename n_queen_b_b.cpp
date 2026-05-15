#include <iostream>
#include <vector>
using namespace std;
void n_queen(vector<vector<char>> board, vector<vector<vector<char>>> &sol, vector<bool> dg1, vector<bool> dg2, vector<bool> col, int row)
{
    if (row == board.size())
    {
        sol.push_back(board);
        return;
    }
    int n = board.size();
    for (int column = 0; column < n; column++)
    {
        if (dg1[row + column] == false && dg2[n - 1 + row - column] == false && col[column] == false)
        {
            board[row][column] = 'Q';
            dg1[row + column] = true;
            dg2[n - 1 + row - column] = true;
            col[column] = true;
            n_queen(board, sol, dg1, dg2, col, row + 1);
            board[row][column] = '.';
            dg1[row + column] = false;
            dg2[n - 1 + row - column] = false;
            col[column] = false;
        }
    }
}
int main()
{
    int n;
    cin >> n;
    vector<vector<char>> board(n, vector<char>(n, '.'));
    vector<bool> dg1(2 * n - 1, false);
    vector<bool> dg2(2 * n - 1, false);
    vector<bool> col(n, false);
    vector<vector<vector<char>>> sol;
    n_queen(board, sol, dg1, dg2, col, 0);
    cout << sol.size() << endl;
    for (auto i : sol)
    {
        for (auto j : i)
        {
            for (auto k : j)
            {
                cout << k;
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
    }
    cout << sol.size() << endl;
    return 0;
}