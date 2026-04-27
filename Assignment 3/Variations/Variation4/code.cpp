#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Edge
{
    int u, v, w;
};
bool cmp(Edge a, Edge b)
{
    return a.w < b.w;
}
int findParent(int node, vector<int> &parent)
{
    if (parent[node] == node)
        return node;
    return parent[node] = findParent(parent[node], parent);
}
void unionSet(int u, int v, vector<int> &parent, vector<int> &rank)
{
    u = findParent(u, parent);
    v = findParent(v, parent);
    if (u != v)
    {
        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[u] > rank[v])
            parent[v] = u;
        else
        {
            parent[v] = u;
            rank[u]++;
        }
    }
}
int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;
    vector<Edge> edges(E);
    for (int i = 0; i < E; i++)
    {
        cout << "Enter source destination weight: ";
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    sort(edges.begin(), edges.end(), cmp);
    vector<int> parent(V), rank(V, 0);
    for (int i = 0; i < V; i++)
        parent[i] = i;
    int totalCost = 0;
    cout << "Edges in MST:\n";
    for (int i = 0; i < E; i++)
    {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (findParent(u, parent) != findParent(v, parent))
        {
            cout << u << " - " << v << " = " << w << endl;
            totalCost += w;
            unionSet(u, v, parent, rank);
        }
    }
    cout << "Minimum Cost: " << totalCost << endl;
    return 0;
}