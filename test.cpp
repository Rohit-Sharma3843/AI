#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;
class State
{
public:
    int x, y, f, g, h;
    string path;
    string mat;
};
class Compare
{
public:
    bool operator()(State s1, State s2)
    {
        return s1.f > s2.f;
    }
};
int get_heuristic(string s)
{
    int ans = 0;
    for (int i = 0; i < 9; i++)
    {
        if (s[i] != '0')
        {
            int gx = ((s[i] - '0') - 1) / 3;
            int gy = ((s[i] - '0') - 1) % 3;
            ans += abs(gx - i / 3) + abs(gy - i % 3);
        }
    }
    return ans;
}
unordered_map<string, pair<string, char>> parent;
void find_path(string dest, string src, unordered_map<string, pair<string, char>> parent)
{
    string moves = "";
    vector<string> ans;

    while (dest != "")
    {
        ans.push_back(dest);
        moves += parent[dest].second;
        dest = parent[dest].first;
    }
    reverse(moves.begin(), moves.end());
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++)

    {
        cout << "MOVE : " << moves[i] << " " << endl;
        for (int j = 0; j < 9; j++)
        {
            cout << ans[i][j] << " ";
            if (j % 3 == 2)
            {
                cout << endl;
            }
        }
        cout << endl
             << endl;
    }
    // cout << moves << endl;
    cout << moves.length() << " " << ans.size() << endl;
}
void solve(string start)
{
    unordered_set<string> visited;
    int sx = -1, sy = -1;
    for (int i = 0; i < start.length(); i++)
    {
        if (start[i] == '0')
        {
            sx = i / 3;
            sy = i % 3;
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

    parent[start] = {"", 'X'};
    priority_queue<State, vector<State>, Compare> pq;
    pq.push(root);
    string goal = "";
    while (!pq.empty())
    {
        auto curr = pq.top();
        pq.pop();
        if (visited.count(curr.mat))
        {
            continue;
        }
        visited.insert(curr.mat);
        if (curr.mat == "123456780")
        {
            goal = curr.mat;
            break;
        }
        int dx[] = {1, 0, -1, 0};
        int dy[] = {0, -1, 0, 1};
        char moves[] = {'D', 'L', 'U', 'R'};
        for (int i = 0; i < 4; i++)
        {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < 3 && ny < 3)
            {
                State child;
                child.mat = curr.mat;
                swap(child.mat[3 * nx + ny], child.mat[3 * curr.x + curr.y]);
                if (visited.count(child.mat))
                {
                    continue;
                }
                child.h = get_heuristic(child.mat);
                child.g = curr.g + 1;
                child.f = child.g + child.h;
                child.path = curr.path + moves[i];
                child.x = nx;
                child.y = ny;
                if (parent.find(child.mat) == parent.end())
                {
                    parent[child.mat] = {curr.mat, moves[i]};
                }
                pq.push(child);
            }
        }
    }
    if (goal == "")
    {
        cout << "No solution" << endl;
        return;
    }
    find_path(goal, start, parent);
}
int main()
{
    string s;
    cin >> s;
    solve(s);
    // 123045678
    return 0;
}