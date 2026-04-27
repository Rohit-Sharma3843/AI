#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
int main()
{
    int V, E;
    cout << "Enter number of cities and roads: ";
    cin >> V >> E;
    vector<vector<pair<int, int>>> adj(V);
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cout << "Enter city1 city2 travel time: ";
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    int src, dest;
    cout << "Enter source city: ";
    cin >> src;
    cout << "Enter destination city: ";
    cin >> dest;
    vector<int> dist(V, INT_MAX), parent(V, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty())
    {
        int node = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if (d > dist[node])
            continue;
        for (auto it : adj[node])
        {
            int next = it.first;
            int wt = it.second;
            if (dist[node] + wt < dist[next])
            {
                dist[next] = dist[node] + wt;
                parent[next] = node;
                pq.push({dist[next], next});
            }
        }
    }
    cout << "Minimum Travel Time: " << dist[dest] << endl;
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v])
        path.push_back(v);
    cout << "Path: ";
    for (int i = path.size() - 1; i >= 0; i--)
    {
        cout << path[i];
        if (i)
            cout << " -> ";
    }
    cout << endl;
    return 0;
}