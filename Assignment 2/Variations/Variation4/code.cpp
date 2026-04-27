#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
using namespace std;
struct Node
{
    int x, y, g, h, f;
};
struct cmp
{
    bool operator()(Node a, Node b) { return a.f > b.f; }
};
int r, c;
vector<vector<char>> grid;
vector<vector<int>> vis;
vector<vector<pair<int, int>>> par;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
bool valid(int x, int y) { return x >= 0 && x < r && y >= 0 && y < c; }
int hfun(int x, int y, int gx, int gy) { return abs(x - gx) + abs(y - gy); }
void pathprint(int gx, int gy)
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
    cout << "\nOptimal Path:\n";
    for (auto i : p)
        cout << "(" << i.first << "," << i.second << ") ";
    cout << "\nSteps: " << p.size() - 1;
}
void astar(int sx, int sy, int gx, int gy)
{
    priority_queue<Node, vector<Node>, cmp> pq;
    pq.push({sx, sy, 0, hfun(sx, sy, gx, gy), hfun(sx, sy, gx, gy)});
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
            cout << "\nPac-Man reached target\n";
            pathprint(gx, gy);
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (valid(nx, ny) && !vis[nx][ny] && grid[nx][ny] != '#' && grid[nx][ny] != 'G')
            {
                int ng = cur.g + 1;
                int nh = hfun(nx, ny, gx, gy);
                pq.push({nx, ny, ng, nh, ng + nh});
                par[nx][ny] = {x, y};
            }
        }
    }
    cout << "\nNo Safe Path Found";
}
int main()
{
    cout << "Enter rows and columns: ";
    cin >> r >> c;
    grid.assign(r, vector<char>(c));
    vis.assign(r, vector<int>(c, 0));
    par.assign(r, vector<pair<int, int>>(c));
    cout << "Enter Grid:\n";
    cout << "P=Pacman D=Dot #=Wall G=Ghost .=Free\n";
    int sx = -1, sy = -1, gx = -1, gy = -1;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> grid[i][j];
            if (grid[i][j] == 'P')
            {
                sx = i;
                sy = j;
            }
            if (grid[i][j] == 'D')
            {
                gx = i;
                gy = j;
            }
        }
    }
    if (sx == -1 || gx == -1)
    {
        cout << "Pacman or Dot Missing";
        return 0;
    }
    astar(sx, sy, gx, gy);
    return 0;
}