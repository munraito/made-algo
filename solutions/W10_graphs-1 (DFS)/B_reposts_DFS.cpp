#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void str_to_lower(string& str) {
    for (char & i : str) {
        i = tolower(i);
    }
}

void print_adj_list(const vector <vector<int> >& g) {
    for (int v = 0; v < g.size(); ++v) {
        cout << v << ": ";
        for (int u : g[v]) {
            cout << u << " ";
        }
        cout << "\n";
    }
}

void dfs(const int& v, vector<int>& used, const vector<vector<int> >& g, vector<int>& chain) {
    used[v] = true;
    chain[v] = 1;
    for (int u : g[v]) {
        if (!used[u]) {
            dfs(u, used, g, chain);
            chain[v] = max(chain[v], chain[u] + 1);
        }
    }
}

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // input
    int n;
    cin >> n;
    string name1, repost, name2;
    vector <vector<int> > g (n + 1, vector<int>());
    map <string, int > name_to_index;
    int ind = 0;
    for (int i = 0; i < n; ++i) {
        cin >> name1 >> repost >> name2;
        str_to_lower(name1);
        str_to_lower(name2);
        if (!name_to_index.count(name2)) {
            name_to_index[name2] = ind++;
        }
        if (!name_to_index.count(name1)) {
            name_to_index[name1] = ind++;
        }
        g[name_to_index[name2]].push_back(name_to_index[name1]);
    }
    // print adjacency list (for debug)
    // print_adj_list(g);
    // search for max depth
    vector<int> used(n + 1, false);
    vector<int> chain (n + 1);
    for (int v = 0; v < n + 1; ++v) {
        if (!used[v]) {
            dfs(v, used, g, chain);
        }
    }
    // output
    cout << chain[0] << "\n";
    return 0;
}

