#include <iostream>
#include <vector>
#include <limits>
using namespace std;
const int R = 6, C = 7;
vector<vector<char>> b(R, vector<char>(C, '.'));
void show()
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
            cout << b[i][j] << " ";
        cout << "\n";
    }
    for (int j = 0; j < C; j++)
        cout << j << " ";
    cout << "\n";
}
bool validMove(int col) { return col >= 0 && col < C && b[0][col] == '.'; }
int drop(int col, char p)
{
    for (int i = R - 1; i >= 0; i--)
    {
        if (b[i][col] == '.')
        {
            b[i][col] = p;
            return i;
        }
    }
    return -1;
}
void undo(int row, int col) { b[row][col] = '.'; }
bool win(char p)
{
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C - 3; j++)
            if (b[i][j] == p && b[i][j + 1] == p && b[i][j + 2] == p && b[i][j + 3] == p)
                return true;
    for (int i = 0; i < R - 3; i++)
        for (int j = 0; j < C; j++)
            if (b[i][j] == p && b[i + 1][j] == p && b[i + 2][j] == p && b[i + 3][j] == p)
                return true;
    for (int i = 0; i < R - 3; i++)
        for (int j = 0; j < C - 3; j++)
            if (b[i][j] == p && b[i + 1][j + 1] == p && b[i + 2][j + 2] == p && b[i + 3][j + 3] == p)
                return true;
    for (int i = 3; i < R; i++)
        for (int j = 0; j < C - 3; j++)
            if (b[i][j] == p && b[i - 1][j + 1] == p && b[i - 2][j + 2] == p && b[i - 3][j + 3] == p)
                return true;
    return false;
}
bool full()
{
    for (int j = 0; j < C; j++)
        if (b[0][j] == '.')
            return false;
    return true;
}
int score()
{
    if (win('O'))
        return 1000;
    if (win('X'))
        return -1000;
    return 0;
}
int minimax(int depth, bool maxi, int alpha, int beta)
{
    int s = score();
    if (depth == 0 || s != 0 || full())
        return s;
    if (maxi)
    {
        int best = -100000;
        for (int col = 0; col < C; col++)
        {
            if (validMove(col))
            {
                int row = drop(col, 'O');
                best = max(best, minimax(depth - 1, false, alpha, beta));
                undo(row, col);
                alpha = max(alpha, best);
                if (beta <= alpha)
                    break;
            }
        }
        return best;
    }
    else
    {
        int best = 100000;
        for (int col = 0; col < C; col++)
        {
            if (validMove(col))
            {
                int row = drop(col, 'X');
                best = min(best, minimax(depth - 1, true, alpha, beta));
                undo(row, col);
                beta = min(beta, best);
                if (beta <= alpha)
                    break;
            }
        }
        return best;
    }
}
int bestMove()
{
    int best = -100000, colAns = 0;
    for (int col = 0; col < C; col++)
    {
        if (validMove(col))
        {
            int row = drop(col, 'O');
            int val = minimax(5, false, -100000, 100000);
            undo(row, col);
            if (val > best)
            {
                best = val;
                colAns = col;
            }
        }
    }
    return colAns;
}
int main()
{
    cout << "Connect Four Game\nYou=X AI=O\n";
    while (true)
    {
        show();
        int col;
        cout << "Enter your column: ";
        cin >> col;
        if (!validMove(col))
        {
            cout << "Invalid Move\n";
            continue;
        }
        drop(col, 'X');
        if (win('X'))
        {
            show();
            cout << "You Win";
            break;
        }
        if (full())
        {
            show();
            cout << "Draw";
            break;
        }
        int ai = bestMove();
        drop(ai, 'O');
        cout << "AI chooses column " << ai << "\n";
        if (win('O'))
        {
            show();
            cout << "AI Wins";
            break;
        }
        if (full())
        {
            show();
            cout << "Draw";
            break;
        }
    }
    return 0;
}