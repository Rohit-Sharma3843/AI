#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    int vertices;
    vector<vector<int>> weight;
    vector<int> heuristic;

    Graph(int v)
    {
        vertices = v;
        weight.resize(v, vector<int>(v, 0));
        heuristic.resize(v);
        create();
    }

    void create()
    {
        int edges;
        cout << "Enter number of edges: ";
        cin >> edges;

        int u, v, w;
        for (int i = 0; i < edges; i++)
        {
            cout << "Enter (u v weight): ";
            cin >> u >> v >> w;
            weight[u][v] = w;
        }

        cout << "Enter heuristic values:\n";
        for (int i = 0; i < vertices; i++)
        {
            cout << "h(" << i << "): ";
            cin >> heuristic[i];
        }
    }

    void Astar(int start, int goal)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        vector<int> g(vertices, INT_MAX);
        vector<int> parent(vertices, -1);
        vector<bool> visited(vertices, false);

        g[start] = 0;
        pq.push({heuristic[start], start});

        while (!pq.empty())
        {
            int node = pq.top().second;
            pq.pop();

            if (visited[node])
                continue;

            visited[node] = true;

            if (node == goal)
                break;

            for (int i = 0; i < vertices; i++)
            {
                if (weight[node][i] > 0)
                {
                    int new_g = g[node] + weight[node][i];

                    if (new_g < g[i])
                    {
                        g[i] = new_g;
                        int f = g[i] + heuristic[i];
                        pq.push({f, i});
                        parent[i] = node;
                    }
                }
            }
        }

        if (g[goal] == INT_MAX)
        {
            cout << "\nNo path found!\n";
            return;
        }

        vector<int> path;
        for (int v = goal; v != -1; v = parent[v])
            path.push_back(v);

        reverse(path.begin(), path.end());

        cout << "\nOptimal Path: ";
        for (int x : path)
            cout << x << " ";

        cout << "\nTotal Cost: " << g[goal] << endl;
    }
};

int main()
{
    int v;
    cout << "Enter number of vertices: ";
    cin >> v;

    Graph g(v);

    int start, goal;
    cout << "Enter start node: ";
    cin >> start;

    cout << "Enter goal node: ";
    cin >> goal;

    g.Astar(start, goal);

    return 0;
}