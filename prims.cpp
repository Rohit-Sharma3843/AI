#include <iostream>
#include <vector>
#include <queue>
#include <map>
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
        int e, v;
        cout << "Enter the number of vertices : ";
        cin >> v;
        this->vertices = v;
        adj.resize(v, vector<pair<int, int>>{});
        cout << "Enter the number of edges : ";
        cin >> e;
        this->edges = e;
        int x, y, w;
        cout << "Enter the edges in u,v,w format :  ";
        for (int i = 0; i < e; i++)
        {
            cin >> x >> y >> w;
            adj[x].push_back({y, w});
            adj[y].push_back({x, w});
        }
    }
    int prims(int start)
    {
        vector<bool> visited(vertices, 0);
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        pq.push({0, {start, -1}});
        vector<pair<int, int>> ans;
        int cost = 0;
        while (!pq.empty())
        {
            auto curr = pq.top();
            pq.pop();
            int weight = curr.first;
            int node = curr.second.first;
            int parent = curr.second.second;
            if (visited[node])
            {
                continue;
            }
            visited[node] = 1;
            cost += weight;
            if (parent != -1)
            {
                ans.push_back({parent, node});
            }
            for (auto neighbours : adj[node])
            {
                int adj_node = neighbours.first;
                int adj_weight = neighbours.second;
                if (!visited[adj_node])
                {
                    pq.push({adj_weight, {adj_node, node}});
                }
            }
        }
        for (auto i : ans)
        {
            cout << i.first << " " << i.second << endl;
        }
        return cost;
    }
};
int main()
{
    Graph *g = new Graph();
    cout << g->prims(0);
    return 0;
}