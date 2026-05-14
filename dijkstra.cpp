#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;
class Graph
{
    int vertices;
    int edges;
    vector<vector<pair<int, int>>> adj;

public:
    Graph()
    {
        int v, e;
        cout << "Enter the number of vertices : ";
        cin >> v;
        this->vertices = v;
        adj.resize(v, vector<pair<int, int>>{});
        cout << "Enter the number of edges : ";
        cin >> e;
        this->edges = e;
        cout << "Enter the edges in u,v,w format : ";
        int x, y, w;
        for (int i = 0; i < edges; i++)
        {
            cin >> x >> y >> w;
            adj[x].push_back({y, w});
            adj[y].push_back({x, w});
        }
    }
    void print_path(vector<int> &parent, int src, int dest)
    {
        vector<int> path;
        while (dest != src)
        {
            path.push_back(dest);
            dest = parent[dest];
        }
        path.push_back(src);
        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i];
            if (i != path.size() - 1)
            {
                cout << " -> ";
            }
        }
    }
    void dijkstra(int source)
    {
        vector<int> dist(vertices, INT32_MAX);
        dist[source] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, source});
        vector<int> parent(vertices, -1);
        while (!pq.empty())
        {
            auto curr = pq.top();
            pq.pop();
            int node = curr.second;
            int weight = curr.first;
            for (auto neighbours : adj[node])
            {
                int adj_node = neighbours.first;
                int adj_dist = neighbours.second;
                if (adj_dist + weight < dist[adj_node])
                {
                    dist[adj_node] = adj_dist + weight;
                    parent[adj_node] = node;
                    pq.push({dist[adj_node], adj_node});
                }
            }
        }
        for (int i = 0; i < vertices; i++)
        {
            cout << "Distance to vertex " << i << " : " << dist[i] << endl;
            print_path(parent, source, i);
            cout << endl;
        }
    }
};
int main()
{
    Graph *g = new Graph();
    g->dijkstra(0);
    // 8 11 0 2 3 0 5 1 2 5 2 2 7 5 7 3 4 3 5 3 5 1 6 1 4 2 1 3 3 3 6 8 7 6 4
    return 0;
}