#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <map>
using namespace std;
class Graph
{
    int vertices;
    int edges;
    vector<vector<int>> adj;

public:
    Graph()
    {
        int e, v;
        cout << "Enter the number of vertices of graph : ";
        cin >> v;
        adj.resize(v, vector<int>{});
        cout << "Enter the number of edges of graph : ";
        cin >> e;
        this->vertices = v;
        this->edges = e;
        int x, y;
        cout << "Enter the edges in u,v format : ";
        for (int i = 0; i < e; i++)
        {
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
    }
    void dfs()
    {
        stack<int> s;
        vector<bool> visited(vertices, 0);
        vector<int> traversal;
        for (int i = 0; i < vertices; i++)
        {
            if (!visited[i])
            {
                s.push(i);
                while (!s.empty())
                {
                    int i = s.top();
                    s.pop();
                    if (!visited[i])
                    {
                        traversal.push_back(i);
                        visited[i] = 1;
                        cout << i << " ";
                        for (int j = adj[i].size() - 1; j >= 0; j -= 1)
                        {
                            s.push(adj[i][j]);
                        }
                    }
                }
            }
        }
    }
    void dfs_util(int i, vector<bool> &visited)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            cout << i << " ";
            for (int j = 0; j < adj[i].size(); j += 1)
            {
                dfs_util(adj[i][j], visited);
            }
        }
    }
    void dfs_rec()
    {
        vector<bool> visited(vertices, 0);
        for (int i = 0; i < vertices; i++)
        {
            if (!visited[i])
            {
                dfs_util(i, visited);
            }
        }
    }
    void bfs()
    {
        queue<int> q;
        vector<bool> visited(vertices, 0);
        for (int i = 0; i < vertices; i++)
        {
            if (!visited[i])
            {
                q.push(i);
                visited[i] = 1;
                while (!q.empty())
                {
                    int j = q.front();
                    q.pop();
                    cout << j << " ";
                    for (int k = 0; k < adj[j].size(); k++)
                    {
                        if (!visited[k])
                        {
                            visited[k] = 1;
                            q.push(k);
                        }
                    }
                }
            }
        }
    }
};
int main()
{
    // 8 9 0 1 0 2 1 3 1 4 2 5 2 6 4 5 5 6 6 7
    // 8 7 0 1 0 2 1 3 1 4 2 5 4 5 6 7
    Graph *g = new Graph();
    g->dfs();
    cout << endl;
    cout << endl;
    g->dfs_rec();
    cout << endl;
    cout << endl;
    g->bfs();
    return 0;
}