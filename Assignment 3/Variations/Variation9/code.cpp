#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int main()
{
    int V, E;
    cout << "Enter number of towns and connections: ";
    cin >> V >> E;
    vector<vector<pair<int, int>>> adj(V);
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cout << "Enter town1 town2 cost: ";
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> visited(V, 0);
    pq.push({0, 0});
    int totalCost = 0;
    cout << "Edges in MST:\n";
    while (!pq.empty())
    {
        int wt = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        if (visited[node])
            continue;
        visited[node] = 1;
        totalCost += wt;
        for (auto it : adj[node])
        {
            if (!visited[it.first])
                pq.push({it.second, it.first});
        }
    }
    cout << "Minimum Total Cost: " << totalCost << endl;
    return 0;
}