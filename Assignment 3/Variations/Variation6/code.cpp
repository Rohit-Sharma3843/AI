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
int findParent(int x, vector<int> &parent)
{
    if (parent[x] == x)
        return x;
    return parent[x] = findParent(parent[x], parent);
}
void unionSet(int a, int b, vector<int> &parent)
{
    a = findParent(a, parent);
    b = findParent(b, parent);
    if (a != b)
        parent[b] = a;
}
int main()
{
    int V, E;
    cout << "Enter number of cities and cable connections: ";
    cin >> V >> E;
    vector<Edge> edges(E);
    for (int i = 0; i < E; i++)
    {
        cout << "Enter city1 city2 cost: ";
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    sort(edges.begin(), edges.end(), cmp);
    vector<int> parent(V);
    for (int i = 0; i < V; i++)
        parent[i] = i;
    int totalCost = 0;
    cout << "Optimal Cable Connections:\n";
    for (int i = 0; i < E; i++)
    {
        if (findParent(edges[i].u, parent) != findParent(edges[i].v, parent))
        {
            cout << edges[i].u << " - " << edges[i].v << " = " << edges[i].w << endl;
            totalCost += edges[i].w;
            unionSet(edges[i].u, edges[i].v, parent);
        }
    }
    cout << "Minimum Total Cable Cost: " << totalCost << endl;
    return 0;
}