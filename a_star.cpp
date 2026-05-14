#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <set>
#include <vector>
using namespace std;
class State
{
public:
    vector<vector<int>> mat;
    int x, y, f, g, h;
    string path;
};
int get_heuristic(vector<vector<int>> &curr)
{
    int ans = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (curr[i][j] != 0)
            {
                int gx = (curr[i][j] - 1) / 3;
                int gy = (curr[i][j] - 1) % 3;
                ans += abs(gx - i) + abs(gy - j);
            }
        }
    }
    return ans;
}
class Compare
{
public:
    bool operator()(State s1, State s2)
    {
        return s1.f > s2.f;
    }
};
string convert(vector<vector<int>> &curr)
{
    string ans = "";
    for (auto i : curr)
    {
        for (auto j : i)
        {
            ans += to_string(j);
        }
    }
    return ans;
}
unordered_map<string, pair<string, char>> parent;
void get_path(string dest, vector<vector<int>> src, unordered_map<string, pair<string, char>> parent)
{
    vector<vector<vector<int>>> solution;
    string moves = "";
    string curr = dest;
    while (curr != "")
    {
        string prev = parent[curr].first;
        char mv = parent[curr].second;
        moves += mv;
        vector<vector<int>> st(3, vector<int>(3));
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                st[i][j] = (curr[i * 3 + j] - '0');
            }
        }
        solution.push_back(st);
        curr = prev;
    }
    solution.push_back(src);
    reverse(solution.begin(), solution.end());
    reverse(moves.begin(), moves.end());
    for (int i = 0; i < solution.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cout << solution[i][j][k] << " ";
            }
            cout << endl;
        }
        if (i == 0)
        {

            cout << "Move : START" << endl;
        }
        else if (i < moves.length())
        {
            cout << "Move : " << moves[i] << endl;
        }
    }
}
void solve(vector<vector<int>> &start)
{
    priority_queue<State, vector<State>, Compare> pq;
    unordered_set<string> visited;
    int sx = -1, sy = -1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (start[i][j] == 0)
            {
                sx = i, sy = j;
                break;
            }
        }
        if (sx != -1 && sy != -1)
        {
            break;
        }
    }
    State root;
    root.mat = start;
    root.x = sx;
    root.y = sy;
    root.h = get_heuristic(start);
    root.g = 0;
    root.f = root.h;
    root.path = "";
    pq.push(root);
    string str = convert(start);
    parent[str] = {"", 'X'};
    string goal = "";
    while (!pq.empty())
    {
        auto curr = pq.top();
        pq.pop();
        string key = convert(curr.mat);
        if (visited.count(key))
        {
            continue;
        }
        visited.insert(key);
        if (curr.h == 0)
        {
            goal = convert(curr.mat);
            break;
        }
        int dx[] = {0, 0, -1, 1};
        int dy[] = {1, -1, 0, 0};
        char moves[] = {'R', 'L', 'U', 'D'};
        for (int i = 0; i < 4; i++)
        {
            int nx = dx[i] + curr.x;
            int ny = dy[i] + curr.y;
            if (nx >= 0 && ny >= 0 && nx < 3 && ny < 3)
            {
                State child = curr;
                swap(child.mat[nx][ny], child.mat[curr.x][curr.y]);
                string c_key = convert(child.mat);
                if (visited.count(c_key))
                {
                    continue;
                }
                child.h = get_heuristic(child.mat);
                child.x = nx;
                child.y = ny;
                child.g = curr.g + 1;
                child.f = child.g + child.h;
                child.path = curr.path + moves[i];
                if (!parent.count(c_key))
                {
                    parent[c_key] = {key, moves[i]};
                }
                pq.push(child);
            }
        }
    }
    if (goal == "")
    {
        cout << "No solution " << endl;
    }
    get_path("123456780", start, parent);
}

int main()
{
    vector<vector<int>> start(3, vector<int>(3));
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> start[i][j];
        }
    }
    solve(start);
    // 1 2 3 0 4 5 6 7 8 9
    return 0;
}