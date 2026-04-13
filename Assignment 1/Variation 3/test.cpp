#include <bits/stdc++.h>
using namespace std;
class SearchEngine
{
public:
    unordered_map<string, vector<string>> graph;
    unordered_map<string, vector<int>> indexMap;
    unordered_map<string, string> synonym;
    string clean(string word)
    {
        for (char &c : word)
            c = tolower(c);
        word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
        if (word.size() > 3 && word.back() == 's')
            word.pop_back();
        if (synonym.count(word))
            word = synonym[word];
        return word;
    }
    void initSynonyms()
    {
        synonym["aircrafts"] = "aircraft";
        synonym["planes"] = "aircraft";
        synonym["jets"] = "aircraft";
    }
    void buildIndex(vector<string> files)
    {
        for (int i = 0; i < files.size(); i++)
        {
            ifstream file(files[i]);
            string line, word;
            vector<string> words;
            getline(file, line);
            stringstream ss(line);
            while (ss >> word)
            {
                word = clean(word);
                words.push_back(word);
                indexMap[word].push_back(i);
            }
            for (int j = 0; j < words.size(); j++)
            {
                for (int k = j + 1; k < words.size(); k++)
                {
                    graph[words[j]].push_back(words[k]);
                    graph[words[k]].push_back(words[j]);
                }
            }
        }
    }
    void bfs(string query)
    {
        query = clean(query);
        if (indexMap.find(query) != indexMap.end())
        {
            cout << "Nearest Documents:\n";
            for (int f : indexMap[query])
                cout << "File" << f + 1 << ".txt ";
            cout << endl;
        }
        else
            cout << "No direct match found\n";
    }
    void dfsUtil(string word, unordered_set<string> &visited)
    {
        cout << word << " ";
        visited.insert(word);
        for (auto &nbr : graph[word])
            if (!visited.count(nbr))
                dfsUtil(nbr, visited);
    }
    void dfs(string query)
    {
        query = clean(query);
        if (graph.find(query) == graph.end())
        {
            cout << "Word not found in graph\n";
            return;
        }
        unordered_set<string> visited;
        cout << "Deep Search (Related Words):\n";
        dfsUtil(query, visited);
        cout << endl;
    }
};
int main()
{
    SearchEngine se;
    se.initSynonyms();
    vector<string> files = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt", "file6.txt", "file7.txt", "file8.txt", "file9.txt", "file10.txt"};
    se.buildIndex(files);
    string query;
    cout << "Enter search word: ";
    cin >> query;
    cout << "\n--- BFS Result ---\n";
    se.bfs(query);
    cout << "\n--- DFS Result ---\n";
    se.dfs(query);
    return 0;
}