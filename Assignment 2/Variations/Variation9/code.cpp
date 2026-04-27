#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
int n, m, turns;
vector<vector<char>> g;
struct P
{
    int x, y;
};
bool valid(int x, int y) { return x >= 0 && x < n && y >= 0 && y < m && g[x][y] != '#'; }
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int dist(P a, P b) { return abs(a.x - b.x) + abs(a.y - b.y); }
P moveHider(P h, P s)
{
    P best = h;
    int mx = dist(h, s);
    for (int i = 0; i < 4; i++)
    {
        int nx = h.x + dx[i], ny = h.y + dy[i];
        if (valid(nx, ny))
        {
            P t = {nx, ny};
            int d = dist(t, s);
            if (d > mx)
            {
                mx = d;
                best = t;
            }
        }
    }
    return best;
}
P moveSeeker(P s, P h)
{
    P best = s;
    int mn = dist(s, h);
    for (int i = 0; i < 4; i++)
    {
        int nx = s.x + dx[i], ny = s.y + dy[i];
        if (valid(nx, ny))
        {
            P t = {nx, ny};
            int d = dist(t, h);
            if (d < mn)
            {
                mn = d;
                best = t;
            }
        }
    }
    return best;
}
void show(P h, P s)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == h.x && j == h.y)
                cout << "H ";
            else if (i == s.x && j == s.y)
                cout << "S ";
            else
                cout << g[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}
int main()
{
    cout << "Enter rows and columns: ";
    cin >> n >> m;
    g.assign(n, vector<char>(m, '.'));
    cout << "Enter grid (. free # wall):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> g[i][j];
    P h, s;
    cout << "Enter Hider Position: ";
    cin >> h.x >> h.y;
    cout << "Enter Seeker Position: ";
    cin >> s.x >> s.y;
    cout << "Enter Max Turns: ";
    cin >> turns;
    if (!valid(h.x, h.y) || !valid(s.x, s.y))
    {
        cout << "Invalid Position";
        return 0;
    }
    for (int t = 1; t <= turns; t++)
    {
        cout << "Turn " << t << "\n";
        show(h, s);
        if (h.x == s.x && h.y == s.y)
        {
            cout << "Seeker Caught Hider";
            return 0;
        }
        h = moveHider(h, s);
        if (h.x == s.x && h.y == s.y)
        {
            cout << "Seeker Caught Hider";
            return 0;
        }
        s = moveSeeker(s, h);
        if (h.x == s.x && h.y == s.y)
        {
            cout << "Seeker Caught Hider";
            return 0;
        }
    }
    cout << "Hider Survived";
    return 0;
}