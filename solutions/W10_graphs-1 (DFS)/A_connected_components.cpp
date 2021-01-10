#include <iostream>
#include <vector>

using namespace std;

const int DEFAULT_COLOR = 0;

void dfs(const int& v, vector<int>& color, const int& cur, const vector<vector<int> >& g) {
    color[v] = cur;
    for (int u : g[v]) {
        if (color[u] == DEFAULT_COLOR) {
            dfs(u, color, cur, g);
        }
    }
}

void print_adj_list(const vector <vector<int> >& g) {
    for (int v = 0; v < g.size(); ++v) {
        cout << v + 1 << ": ";
        for (int u : g[v]) {
            cout << u + 1 << " ";
        }
        cout << "\n";
    }
}

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    int n, m, b, e;
    cin >> n >> m;
    vector <vector<int> > g (n, vector<int>());
    for (int i = 0; i < m; ++i) {
        cin >> b >> e;
        --b;
        --e;
        g[b].push_back(e);
        g[e].push_back(b);
    }
    // print adjacency list (for debug)
    // print_adj_list(g);
    // search for components in the graph
    vector<int> color(n, DEFAULT_COLOR);
    int cnt = 0;
    for (int v = 0; v < n; ++v) { // vector<int> v : g
        if (color[v] == DEFAULT_COLOR) {
            ++cnt;
            dfs(v, color, cnt, g);
        }
    }
    // output
    cout << cnt << "\n";
    for (int c : color) {
        cout << c << " ";
    }
    return 0;
}

