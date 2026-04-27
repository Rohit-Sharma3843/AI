#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;
struct Node
{
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f)
    {
        ch = c;
        freq = f;
        left = right = NULL;
    }
};
struct cmp
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};
void generateCodes(Node *root, string code, unordered_map<char, string> &huff)
{
    if (!root)
        return;
    if (!root->left && !root->right)
        huff[root->ch] = code;
    generateCodes(root->left, code + "0", huff);
    generateCodes(root->right, code + "1", huff);
}
int main()
{
    string text;
    cout << "Enter text: ";
    getline(cin, text);
    unordered_map<char, int> freq;
    for (char c : text)
        freq[c]++;
    priority_queue<Node *, vector<Node *>, cmp> pq;
    for (auto x : freq)
        pq.push(new Node(x.first, x.second));
    while (pq.size() > 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        Node *merged = new Node('$', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }
    Node *root = pq.top();
    unordered_map<char, string> huff;
    generateCodes(root, "", huff);
    cout << "Huffman Codes:\n";
    for (auto x : huff)
        cout << x.first << " : " << x.second << endl;
    string encoded = "";
    for (char c : text)
        encoded += huff[c];
    cout << "Encoded Text: " << encoded << endl;
    int originalSize = text.length() * 8;
    int compressedSize = encoded.length();
    cout << "Original Size: " << originalSize << " bits" << endl;
    cout << "Compressed Size: " << compressedSize << " bits" << endl;
    cout << "Compression Ratio: " << (float)compressedSize / originalSize << endl;
    return 0;
}