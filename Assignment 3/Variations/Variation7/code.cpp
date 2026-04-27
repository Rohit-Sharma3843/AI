#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
int main()
{
    int V, E;
    cout << "Enter number of locations and roads: ";
    cin >> V >> E;
    vector<vector<pair<int, int>>> adj(V);
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cout << "Enter source destination time: ";
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    int src;
    cout << "Enter starting location: ";
    cin >> src;
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty())
    {
        int d = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        for (auto it : adj[node])
        {
            int next = it.first;
            int wt = it.second;
            if (dist[node] + wt < dist[next])
            {
                dist[next] = dist[node] + wt;
                pq.push({dist[next], next});
            }
        }
    }
    cout << "Shortest Travel Times from Location " << src << ":\n";
    for (int i = 0; i < V; i++)
        cout << "To " << i << " = " << dist[i] << endl;
    return 0;
}