#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
class graph
{
public:
    vector<vector<int>> adjacency;
    int edges;
    int vertices;
    void create()
    {
        int edges;
        cout << "Enter the number of edges : ";
        cin >> edges;
        this->edges = edges;
        int x, y;
        for (int i = 0; i < edges; i++)
        {
            cout << "Enter the edge " << i + 1 << " in (u,v) format : ";
            cin >> x >> y;
            adjacency[x][y] = 1;
            adjacency[y][x] = 1;
        }
    }
    graph(int vertices)
    {
        this->vertices = vertices;
        vector<vector<int>> v(vertices, vector<int>(vertices, 0));
        adjacency = v;
        create();
    }
    void itr_dfs(int i)
    {
        stack<int> s;
        int j;
        s.push(i);
        bool visited[vertices] = {0};
        while (!s.empty())
        {
            i = s.top();
            s.pop();
            if (!visited[i])
            {
                cout << i << " ";
                visited[i] = 1;
                for (int j = 0; j < vertices; j++)
                {
                    if (adjacency[i][j] == 1 && !visited[j])
                    {
                        s.push(j);
                    }
                }
            }
        }
    }
    void rec_dfs(int i)
    {
        static vector<bool> visited(vertices, 0);
        cout << i << " ";
        int j;
        visited[i] = 1;
        for (j = 0; j < vertices; j++)
        {
            if (adjacency[i][j] == 1 && !visited[j])
            {
                rec_dfs(j);
            }
        }
    }
    void bfs(int i)
    {
        queue<int> q;
        cout << i << " ";
        q.push(i);
        vector<int> visited(vertices, 0);
        visited[i] = 1;
        while (!q.empty())
        {
            i = q.front();
            q.pop();
            for (int j = 0; j < vertices; j++)
            {
                if (!visited[j] && adjacency[i][j] == 1)
                {
                    visited[j] = 1;
                    cout << j << " ";
                    q.push(j);
                }
            }
        }
    }
};
int main()
{
    int n;
    cout << "Enter the number of vertices : ";
    cin >> n;
    graph g(n);
    cout << endl;
    for (int i = 0; i < g.vertices; i++)
    {
        for (int j : g.adjacency[i])
        {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Iterative DFS of the graph : ";
    g.itr_dfs(0);
    cout << endl;
    cout << "Recursive DFS of the graph : ";
    g.rec_dfs(0);
    cout << endl;
    cout << "BFS of the graph : ";
    g.bfs(0);
    //   6 0 1 0 3 1 2 1 3 2 4 3 4
    return 0;
}