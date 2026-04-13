#include <bits/stdc++.h>
using namespace std;

class Graph
{
public:
    vector<vector<int>> adj;
    vector<string> states;
    unordered_map<string, int> mp;
    int V;

    Graph(int v)
    {
        V = v;
        adj.assign(V, vector<int>(V, 0));
    }

    void setStates()
    {
        states = {
            "Greeting", "Product", "Laptop", "Mobile",
            "Gaming", "Office", "Student",
            "Brand", "Apple", "Dell", "HP",
            "Budget", "Low", "Mid", "High",
            "Price", "End"};

        for (int i = 0; i < states.size(); i++)
        {
            mp[states[i]] = i;
        }
    }

    void buildGraph()
    {

        adj[mp["Greeting"]][mp["Product"]] = 1;
        adj[mp["Product"]][mp["Laptop"]] = 1;
        adj[mp["Product"]][mp["Mobile"]] = 1;
        adj[mp["Laptop"]][mp["Gaming"]] = 1;
        adj[mp["Laptop"]][mp["Office"]] = 1;
        adj[mp["Laptop"]][mp["Student"]] = 1;
        adj[mp["Gaming"]][mp["Brand"]] = 1;
        adj[mp["Office"]][mp["Brand"]] = 1;
        adj[mp["Student"]][mp["Brand"]] = 1;
        adj[mp["Brand"]][mp["Apple"]] = 1;
        adj[mp["Brand"]][mp["Dell"]] = 1;
        adj[mp["Brand"]][mp["HP"]] = 1;
        adj[mp["Apple"]][mp["Budget"]] = 1;
        adj[mp["Dell"]][mp["Budget"]] = 1;
        adj[mp["HP"]][mp["Budget"]] = 1;
        adj[mp["Budget"]][mp["Low"]] = 1;
        adj[mp["Budget"]][mp["Mid"]] = 1;
        adj[mp["Budget"]][mp["High"]] = 1;
        adj[mp["Low"]][mp["Price"]] = 1;
        adj[mp["Mid"]][mp["Price"]] = 1;
        adj[mp["High"]][mp["Price"]] = 1;
        adj[mp["Price"]][mp["End"]] = 1;
    }

    void generateFlow(string input)
    {
        string type = "", usage = "", brand = "", budget = "";
        if (input.find("laptop") != string::npos)
            type = "Laptop";
        else if (input.find("mobile") != string::npos)
            type = "Mobile";
        else
            type = "Laptop";
        if (input.find("gaming") != string::npos)
            usage = "Gaming";
        else if (input.find("office") != string::npos)
            usage = "Office";
        else
            usage = "Student";
        if (input.find("dell") != string::npos)
            brand = "Dell";
        else if (input.find("hp") != string::npos)
            brand = "HP";
        else
            brand = "Apple";
        if (input.find("cheap") != string::npos || input.find("low") != string::npos)
            budget = "Low";
        else if (input.find("mid") != string::npos)
            budget = "Mid";
        else
            budget = "High";
        vector<string> flow = {
            "Greeting", "Product", type, usage,
            "Brand", brand, "Budget", budget,
            "Price", "End"};
        cout << "\nChatbot Flow:\n";
        for (int i = 0; i < flow.size(); i++)
        {
            if (i != 0)
                cout << "->";
            cout << flow[i];
        }
        cout << endl;
    }
};
int main()
{
    Graph g(17);
    g.setStates();
    g.buildGraph();
    string input;
    cout << "Enter your query: ";
    getline(cin, input);
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    g.generateFlow(input);
    return 0;
}