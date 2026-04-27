#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Node
{
    int x, y;
    int g, h, f;
};

struct Compare
{
    bool operator()(Node a, Node b)
    {
        return a.f > b.f;
    }
};

int ROW, COL;

vector<vector<int>> grid;
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
    return grid[x][y] == 1;
}

int heuristic(int x, int y, int gx, int gy)
{
    return abs(x - gx) + abs(y - gy);
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
    {
        cout << "(" << p.first << "," << p.second << ") ";
    }

    cout << endl;
}

void aStar(int sx, int sy, int gx, int gy)
{
    priority_queue<Node, vector<Node>, Compare> pq;

    pq.push({sx, sy, 0,
             heuristic(sx, sy, gx, gy),
             heuristic(sx, sy, gx, gy)});

    parentCell[sx][sy] = {-1, -1};

    while (!pq.empty())
    {
        Node cur = pq.top();
        pq.pop();

        int x = cur.x;
        int y = cur.y;

        if (visited[x][y])
            continue;

        visited[x][y] = true;

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
                int gNew = cur.g + 1;
                int hNew = heuristic(nx, ny, gx, gy);
                int fNew = gNew + hNew;

                pq.push({nx, ny, gNew, hNew, fNew});
                parentCell[nx][ny] = {x, y};
            }
        }
    }

    cout << "\nNo Path Found\n";
}

int main()
{
    cout << "Enter number of rows and columns: ";
    cin >> ROW >> COL;

    grid.assign(ROW, vector<int>(COL));
    visited.assign(ROW, vector<bool>(COL, false));
    parentCell.assign(ROW, vector<pair<int, int>>(COL));

    cout << "\nEnter Grid Values:\n";
    cout << "0 = Free Cell, 1 = Obstacle\n\n";

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            cin >> grid[i][j];
        }
    }

    int sx, sy, gx, gy;

    cout << "\nEnter Start Position (row col): ";
    cin >> sx >> sy;

    cout << "Enter Goal Position (row col): ";
    cin >> gx >> gy;

    if (!isValid(sx, sy) || !isValid(gx, gy))
    {
        cout << "Invalid Coordinates\n";
        return 0;
    }

    if (isBlocked(sx, sy) || isBlocked(gx, gy))
    {
        cout << "Start or Goal is blocked\n";
        return 0;
    }

    aStar(sx, sy, gx, gy);

    return 0;
}