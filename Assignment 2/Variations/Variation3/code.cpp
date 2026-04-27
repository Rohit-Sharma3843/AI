#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
using namespace std;
struct State
{
    int wkx, wky, wqx, wqy, bkx, bky;
    bool whiteTurn;
};
bool valid(int x, int y) { return x >= 0 && x < 8 && y >= 0 && y < 8; }
bool same(int a, int b, int c, int d) { return a == c && b == d; }
bool kingNear(int x1, int y1, int x2, int y2) { return abs(x1 - x2) <= 1 && abs(y1 - y2) <= 1; }
bool queenAttack(int qx, int qy, int x, int y)
{
    if (qx == x || qy == y)
        return true;
    if (abs(qx - x) == abs(qy - y))
        return true;
    return false;
}
bool blackInCheck(State s)
{
    return queenAttack(s.wqx, s.wqy, s.bkx, s.bky) || kingNear(s.wkx, s.wky, s.bkx, s.bky);
}
bool legalState(State s)
{
    if (!valid(s.wkx, s.wky) || !valid(s.wqx, s.wqy) || !valid(s.bkx, s.bky))
        return false;
    if (same(s.wkx, s.wky, s.wqx, s.wqy))
        return false;
    if (same(s.wkx, s.wky, s.bkx, s.bky))
        return false;
    if (same(s.wqx, s.wqy, s.bkx, s.bky))
        return false;
    if (kingNear(s.wkx, s.wky, s.bkx, s.bky))
        return false;
    return true;
}
vector<State> whiteMoves(State s)
{
    vector<State> v;
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0)
                continue;
            State t = s;
            t.wkx += dx;
            t.wky += dy;
            t.whiteTurn = false;
            if (legalState(t) && !kingNear(t.wkx, t.wky, t.bkx, t.bky))
                v.push_back(t);
        }
    }
    int qdx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    int qdy[8] = {0, 0, 1, -1, 1, -1, 1, -1};
    for (int d = 0; d < 8; d++)
    {
        for (int step = 1; step < 8; step++)
        {
            State t = s;
            t.wqx += qdx[d] * step;
            t.wqy += qdy[d] * step;
            t.whiteTurn = false;
            if (!valid(t.wqx, t.wqy))
                break;
            if (same(t.wqx, t.wqy, t.wkx, t.wky))
                break;
            if (same(t.wqx, t.wqy, t.bkx, t.bky))
                break;
            if (legalState(t))
                v.push_back(t);
        }
    }
    return v;
}
vector<State> blackMoves(State s)
{
    vector<State> v;
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0)
                continue;
            State t = s;
            t.bkx += dx;
            t.bky += dy;
            t.whiteTurn = true;
            if (!legalState(t))
                continue;
            if (queenAttack(t.wqx, t.wqy, t.bkx, t.bky))
                continue;
            if (kingNear(t.wkx, t.wky, t.bkx, t.bky))
                continue;
            v.push_back(t);
        }
    }
    return v;
}
bool checkmate(State s)
{
    if (!blackInCheck(s))
        return false;
    vector<State> m = blackMoves(s);
    return m.size() == 0;
}
int evaluate(State s)
{
    if (checkmate(s))
        return 1000;
    int dist = abs(s.bkx - 3) + abs(s.bky - 3);
    return 100 - dist;
}
int minimax(State s, int depth, bool maxPlayer)
{
    if (depth == 0 || checkmate(s))
        return evaluate(s);
    if (maxPlayer)
    {
        int best = -100000;
        vector<State> m = whiteMoves(s);
        for (auto x : m)
            best = max(best, minimax(x, depth - 1, false));
        return best;
    }
    else
    {
        int best = 100000;
        vector<State> m = blackMoves(s);
        if (m.size() == 0)
            return evaluate(s);
        for (auto x : m)
            best = min(best, minimax(x, depth - 1, true));
        return best;
    }
}
State bestMove(State s, int depth)
{
    vector<State> m = whiteMoves(s);
    int best = -100000;
    State ans = s;
    for (auto x : m)
    {
        int val = minimax(x, depth - 1, false);
        if (val > best)
        {
            best = val;
            ans = x;
        }
    }
    return ans;
}
int main()
{
    State s;
    cout << "Enter White King Position: ";
    cin >> s.wkx >> s.wky;
    cout << "Enter White Queen Position: ";
    cin >> s.wqx >> s.wqy;
    cout << "Enter Black King Position: ";
    cin >> s.bkx >> s.bky;
    s.whiteTurn = true;
    if (!legalState(s))
    {
        cout << "Invalid Board State";
        return 0;
    }
    State r = bestMove(s, 3);
    cout << "\nBest White Move:\n";
    cout << "White King: " << r.wkx << " " << r.wky << "\n";
    cout << "White Queen: " << r.wqx << " " << r.wqy << "\n";
    cout << "Black King: " << r.bkx << " " << r.bky << "\n";
    if (checkmate(r))
        cout << "Checkmate Found\n";
    else
        cout << "Best Strategic Move Played\n";
    return 0;
}