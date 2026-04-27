#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n, m, wallp;
vector<vector<char>> g;
vector<vector<int>> vis;
vector<vector<pair<int, int>>> par;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
bool valid(int x, int y) { return x >= 0 && x < n && y >= 0 && y < m; }
void generate()
{
    g.assign(n, vector<char>(m, '.'));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if ((i == 0 && j == 0) || (i == n - 1 && j == m - 1))
                continue;
            int r = rand() % 100;
            if (r < wallp)
                g[i][j] = '#';
        }
    }
    g[0][0] = 'S';
    g[n - 1][m - 1] = 'G';
}
bool bfs()
{
    queue<pair<int, int>> q;
    vis.assign(n, vector<int>(m, 0));
    par.assign(n, vector<pair<int, int>>(m));
    q.push({0, 0});
    vis[0][0] = 1;
    par[0][0] = {-1, -1};
    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        int x = cur.first, y = cur.second;
        if (x == n - 1 && y == m - 1)
            return true;
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (valid(nx, ny) && !vis[nx][ny] && g[nx][ny] != '#')
            {
                vis[nx][ny] = 1;
                par[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }
    return false;
}
void markPath()
{
    int x = n - 1, y = m - 1;
    while (!(x == -1 && y == -1))
    {
        if (g[x][y] == '.')
            g[x][y] = '*';
        int px = par[x][y].first, py = par[x][y].second;
        x = px;
        y = py;
    }
    g[0][0] = 'S';
    g[n - 1][m - 1] = 'G';
}
void printGrid()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << g[i][j] << " ";
        cout << "\n";
    }
}
int main()
{
    srand(time(0));
    cout << "Enter rows and columns: ";
    cin >> n >> m;
    cout << "Enter wall percentage (0 to 60): ";
    cin >> wallp;
    while (true)
    {
        generate();
        if (bfs())
            break;
    }
    markPath();
    cout << "\nGenerated Playable Dungeon:\n";
    printGrid();
    cout << "\nS=Start G=Goal #=Wall *=Shortest Path";
    return 0;
}