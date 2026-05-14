#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
class Graph
{
    int vertices;
    vector<pair<pair<int, int>, int>> edges;

public:
    Graph()
    {
        int e, v;
        cout << "Enter the number of vertices : ";
        cin >> v;
        this->vertices = v;
        cout << "Enter the number of edges : ";
        cin >> e;
        int x, y, w;
        cout << "Enter the edges in u,v,w format :  ";
        for (int i = 0; i < e; i++)
        {
            cin >> x >> y >> w;
            edges.push_back({{x, y}, w});
        }
    }
    int unite(int u, int v, vector<int> &parent)
    {
        parent[v] = u;
    }
    int get_parent(int u, vector<int> &parent)
    {
        if (parent[u] == u)
        {
            return u;
        }
        return get_parent(parent[u], parent);
    }
    void kruskal()
    {
        sort(edges.begin(), edges.end(),
             [](auto &a, auto &b)
             {
                 return a.second < b.second;
             });
        int cost = 0;
        vector<int> parent(vertices);
        for (int i = 0; i < vertices; i++)
        {
            parent[i] = i;
        }
        vector<pair<int, int>> ans;
        for (int i = 0; i < edges.size(); i++)
        {
            int u = get_parent(edges[i].first.first, parent);
            int v = get_parent(edges[i].first.second, parent);
            if (u != v)
            {
                unite(u, v, parent);
                ans.push_back({edges[i].first.first, edges[i].first.second});
                cost += edges[i].second;
            }
        }
        for (auto i : ans)
        {
            cout << i.first << " " << i.second << endl;
        }
        cout << "Cost : " << cost << endl;
    }
};
int main()
{
    Graph *g = new Graph();
    g->kruskal();
    return 0;
}