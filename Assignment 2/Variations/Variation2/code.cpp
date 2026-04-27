#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
int ROW, COL;
vector<vector<int>> maze;
vector<vector<bool>> visited;
vector<vector<pair<int, int>>> parentCell;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
bool isValid(int x, int y)
{
    return (x >= 0 && x < ROW && y >= 0 && y < COL);
}
bool isBlocked(int x, int y)
{
    return maze[x][y] == 1;
}
void printPath(int gx, int gy)
{
    vector<pair<int, int>> path;
    int x = gx;
    int y = gy;
    while (!(x == -1 && y == -1))
    {
        path.push_back({x, y});

        int px = parentCell[x][y].first;
        int py = parentCell[x][y].second;

        x = px;
        y = py;
    }
    reverse(path.begin(), path.end());
    cout << "\nShortest Path:\n";
    for (auto p : path)
        cout << "(" << p.first << "," << p.second << ") ";
    cout << "\nTotal Steps: " << path.size() - 1 << endl;
}
void bfs(int sx, int sy, int gx, int gy)
{
    queue<pair<int, int>> q;
    q.push({sx, sy});
    visited[sx][sy] = true;
    parentCell[sx][sy] = {-1, -1};
    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        int x = cur.first;
        int y = cur.second;
        if (x == gx && y == gy)
        {
            cout << "\nGoal Reached Successfully\n";
            printPath(gx, gy);
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isValid(nx, ny) &&
                !isBlocked(nx, ny) &&
                !visited[nx][ny])
            {
                visited[nx][ny] = true;
                parentCell[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }
    cout << "\nNo Path Found\n";
}
int main()
{
    cout << "Enter rows and columns: ";
    cin >> ROW >> COL;
    maze.assign(ROW, vector<int>(COL));
    visited.assign(ROW, vector<bool>(COL, false));
    parentCell.assign(ROW, vector<pair<int, int>>(COL));
    cout << "\nEnter Maze Grid:\n";
    cout << "0 = Free Cell, 1 = Wall\n\n";
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            cin >> maze[i][j];
    int sx, sy, gx, gy;
    cout << "\nEnter Start Position (row col): ";
    cin >> sx >> sy;
    cout << "Enter Goal Position (row col): ";
    cin >> gx >> gy;
    if (sx < 0 || sy < 0 || gx < 0 || gy < 0 ||
        sx >= ROW || sy >= COL || gx >= ROW || gy >= COL)
    {
        cout << "Invalid Coordinates\n";
        return 0;
    }
    if (maze[sx][sy] == 1 || maze[gx][gy] == 1)
    {
        cout << "Start or Goal is blocked\n";
        return 0;
    }
    bfs(sx, sy, gx, gy);
    return 0;
}