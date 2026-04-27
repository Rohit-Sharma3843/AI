#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;
struct Card
{
    int rank;
    char suit;
};
vector<Card> deck;
int value(Card c) { return c.rank; }
string nameCard(Card c)
{
    string r;
    if (c.rank <= 10 && c.rank >= 2)
        r = to_string(c.rank);
    else if (c.rank == 11)
        r = "J";
    else if (c.rank == 12)
        r = "Q";
    else if (c.rank == 13)
        r = "K";
    else
        r = "A";
    return r + c.suit;
}
void makeDeck()
{
    deck.clear();
    char suits[4] = {'H', 'D', 'S', 'C'};
    for (int s = 0; s < 4; s++)
        for (int r = 2; r <= 14; r++)
            deck.push_back({r, suits[s]});
}
void removeCard(Card c)
{
    for (int i = 0; i < deck.size(); i++)
    {
        if (deck[i].rank == c.rank && deck[i].suit == c.suit)
        {
            deck.erase(deck.begin() + i);
            return;
        }
    }
}
int score5(vector<Card> v)
{
    vector<int> cnt(15, 0);
    for (auto x : v)
        cnt[x.rank]++;
    bool flush = true;
    for (int i = 1; i < v.size(); i++)
        if (v[i].suit != v[0].suit)
            flush = false;
    vector<int> ranks;
    for (auto x : v)
        ranks.push_back(x.rank);
    sort(ranks.begin(), ranks.end());
    bool straight = true;
    for (int i = 1; i < 5; i++)
        if (ranks[i] != ranks[i - 1] + 1)
            straight = false;
    int four = 0, three = 0, pairs = 0, high = ranks[4];
    for (int i = 2; i <= 14; i++)
    {
        if (cnt[i] == 4)
            four = i;
        if (cnt[i] == 3)
            three = i;
        if (cnt[i] == 2)
            pairs++;
    }
    if (straight && flush)
        return 800 + high;
    if (four)
        return 700 + four;
    if (three && pairs)
        return 600 + three;
    if (flush)
        return 500 + high;
    if (straight)
        return 400 + high;
    if (three)
        return 300 + three;
    if (pairs == 2)
        return 200 + high;
    if (pairs == 1)
        return 100 + high;
    return high;
}
int bestScore(vector<Card> all)
{
    int best = 0;
    for (int a = 0; a < 7; a++)
        for (int b = a + 1; b < 7; b++)
            for (int c = b + 1; c < 7; c++)
                for (int d = c + 1; d < 7; d++)
                    for (int e = d + 1; e < 7; e++)
                    {
                        vector<Card> t = {all[a], all[b], all[c], all[d], all[e]};
                        best = max(best, score5(t));
                    }
    return best;
}
double simulate(vector<Card> my, vector<Card> table, int trials)
{
    int win = 0;
    for (int t = 0; t < trials; t++)
    {
        vector<Card> d = deck;
        random_shuffle(d.begin(), d.end());
        vector<Card> opp = {d[0], d[1]};
        int idx = 2;
        vector<Card> tab = table;
        while (tab.size() < 5)
        {
            tab.push_back(d[idx]);
            idx++;
        }
        vector<Card> mine = my, his = opp;
        for (auto x : tab)
        {
            mine.push_back(x);
            his.push_back(x);
        }
        int s1 = bestScore(mine);
        int s2 = bestScore(his);
        if (s1 >= s2)
            win++;
    }
    return (double)win / trials;
}
int main()
{
    srand(time(0));
    makeDeck();
    vector<Card> my(2), table;
    cout << "Enter Your 2 Cards (rank suit):\n";
    for (int i = 0; i < 2; i++)
    {
        cin >> my[i].rank >> my[i].suit;
        removeCard(my[i]);
    }
    int n;
    cout << "Enter Number of Community Cards (0 to 5): ";
    cin >> n;
    cout << "Enter Community Cards:\n";
    for (int i = 0; i < n; i++)
    {
        Card x;
        cin >> x.rank >> x.suit;
        table.push_back(x);
        removeCard(x);
    }
    double p = simulate(my, table, 3000);
    cout << "\nWinning Probability: " << p * 100 << "%\n";
    if (p > 0.7)
        cout << "AI Decision: RAISE";
    else if (p > 0.45)
        cout << "AI Decision: CALL";
    else
        cout << "AI Decision: FOLD";
    return 0;
}