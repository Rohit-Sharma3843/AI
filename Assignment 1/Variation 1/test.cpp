#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    vector<vector<int>> adj;
    int V;
    vector<string> concepts;
    unordered_map<string, int> mp;

    Graph(int v)
    {
        V = v;
        adj.assign(V, vector<int>(V, 0));
        concepts.resize(V);
    }

    void inputConcepts()
    {
        cout << "Enter concepts:\n";
        for (int i = 0; i < V; i++)
        {
            cin >> concepts[i];
            mp[concepts[i]] = i;
        }
    }

    void createEdges()
    {
        int e;
        cout << "Enter number of relations: ";
        cin >> e;

        string u, v;
        cout << "Enter relations (u v):\n";
        for (int i = 0; i < e; i++)
        {
            cin >> u >> v;
            int x = mp[u];
            int y = mp[v];

            adj[x][y] = 1;
            adj[y][x] = 1;
        }
    }

    void bfs(string start)
    {
        vector<bool> visited(V, false);
        queue<int> q;

        q.push(mp[start]);
        visited[mp[start]] = true;

        bool first = true;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            if (!first)
                cout << "->";
            cout << concepts[node];
            first = false;

            for (int i = 0; i < V; i++)
            {
                if (adj[node][i] && !visited[i])
                {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }

    void dfsUtil(int node, vector<bool> &visited)
    {
        visited[node] = true;
        cout << concepts[node];

        for (int i = 0; i < V; i++)
        {
            if (adj[node][i] && !visited[i])
            {
                cout << "->";
                dfsUtil(i, visited);
            }
        }
    }

    void dfs(string start)
    {
        vector<bool> visited(V, false);
        dfsUtil(mp[start], visited);
    }
};

int main()
{
    int V;
    cout << "Enter number of concepts: ";
    cin >> V;

    Graph g(V);

    g.inputConcepts();
    g.createEdges();

    string start;
    cout << "Enter starting concept: ";
    cin >> start;

    cout << "\nBFS Traversal:\n";
    g.bfs(start);

    cout << "\nDFS Traversal:\n";
    g.dfs(start);

    return 0;
}