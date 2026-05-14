#include <iostream>
#include <vector>
using namespace std;
bool valid_move(vector<vector<char>> &board, int row, int col)
{
    for (int i = 0; i < board.size(); i++)
    {
        if (board[row][i] == 'Q' || board[i][col] == 'Q')
        {
            return false;
        }
    }
    int i = row, j = col;
    while (i < board.size() && j >= 0)
    {
        if (board[i][j] == 'Q')
        {
            return false;
        }
        i++, j--;
    }
    i = row, j = col;
    while (i >= 0 && j < board.size())
    {
        if (board[i][j] == 'Q')
        {
            return false;
        }
        i--, j++;
    }
    i = row, j = col;
    while (i >= 0 && j >= 0)
    {
        if (board[i][j] == 'Q')
        {
            return false;
        }
        i--, j--;
    }
    i = row, j = col;
    while (i < board.size() && j < board.size())
    {
        if (board[i][j] == 'Q')
        {
            return false;
        }
        i++, j++;
    }
    return true;
}
void n_queens(vector<vector<char>> &board, vector<vector<string>> &ans, int row)
{
    if (row == board.size())
    {
        vector<string> s;
        string st = "";
        for (auto i : board)
        {
            for (auto j : i)
            {
                cout << j << " ";
                st += j;
            }
            cout << endl;
            s.push_back(st);
        }
        cout << "\n\n";
        ans.push_back(s);
        return;
    }
    for (int j = 0; j < board.size(); j++)
    {
        if (board[row][j] == '.')
        {
            if (valid_move(board, row, j))
            {
                board[row][j] = 'Q';
                n_queens(board, ans, row + 1);
                board[row][j] = '.';
            }
        }
    }
}
int main()
{
    int n;
    cin >> n;
    vector<vector<char>> board(n, vector<char>(n, '.'));
    vector<vector<string>> sol;
    n_queens(board, sol, 0);
    cout << endl;
    cout << sol.size() << endl;
    return 0;
}