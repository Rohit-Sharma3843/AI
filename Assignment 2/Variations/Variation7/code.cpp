#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;
struct Node
{
    int x, y, g, h, f;
};
struct cmp
{
    bool operator()(Node a, Node b) { return a.f > b.f; }
};
int n, m;
vector<vector<int>> grid;
vector<vector<int>> vis;
vector<vector<pair<int, int>>> par;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
bool valid(int x, int y) { return x >= 0 && x < n && y >= 0 && y < m; }
int hfun(int x, int y, int gx, int gy) { return abs(x - gx) + abs(y - gy); }
void printPath(int gx, int gy)
{
    vector<pair<int, int>> p;
    int x = gx, y = gy;
    while (!(x == -1 && y == -1))
    {
        p.push_back({x, y});
        int px = par[x][y].first, py = par[x][y].second;
        x = px;
        y = py;
    }
    reverse(p.begin(), p.end());
    cout << "Troop Path:\n";
    for (auto i : p)
        cout << "(" << i.first << "," << i.second << ") ";
    cout << "\nSteps: " << p.size() - 1 << "\n";
}
bool astar(int sx, int sy, int gx, int gy)
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({sx, sy, 0, hfun(sx, sy, gx, gy), hfun(sx, sy, gx, gy)});
    vis.assign(n, vector<int>(m, 0));
    par.assign(n, vector<pair<int, int>>(m));
    par[sx][sy] = {-1, -1};
    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();
        int x = cur.x, y = cur.y;
        if (vis[x][y])
            continue;
        vis[x][y] = 1;
        if (x == gx && y == gy)
        {
            printPath(gx, gy);
            return true;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (valid(nx, ny) && !vis[nx][ny] && grid[nx][ny] != 1)
            {
                int ng = cur.g + 1, nh = hfun(nx, ny, gx, gy);
                pq.push({nx, ny, ng, nh, ng + nh});
                par[nx][ny] = {x, y};
            }
        }
    }
    return false;
}
int main()
{
    cout << "Enter rows and columns: ";
    cin >> n >> m;
    grid.assign(n, vector<int>(m));
    cout << "Enter Map Grid:\n0=Free 1=Blocked 2=GoldMine 3=EnemyBase\n";
    int tx = -1, ty = -1, gx = -1, gy = -1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
            if (grid[i][j] == 2)
            {
                gx = i;
                gy = j;
            }
            if (grid[i][j] == 3)
            {
                tx = i;
                ty = j;
            }
        }
    }
    int sx, sy, res;
    cout << "Enter Troop Start Position: ";
    cin >> sx >> sy;
    cout << "Enter Current Resources: ";
    cin >> res;
    if (!valid(sx, sy) || grid[sx][sy] == 1)
    {
        cout << "Invalid Start";
        return 0;
    }
    cout << "\nAI Decision:\n";
    if (res < 50 && gx != -1)
    {
        cout << "Need resources first\n";
        if (astar(sx, sy, gx, gy))
            cout << "Collecting Gold\n";
        else
            cout << "No Path to GoldMine\n";
    }
    else if (tx != -1)
    {
        cout << "Attack Enemy Base\n";
        if (astar(sx, sy, tx, ty))
            cout << "Troops Engaged\n";
        else
            cout << "No Path to Enemy Base\n";
    }
    else
        cout << "No Objective Found";
    return 0;
}