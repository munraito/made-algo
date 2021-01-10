#include <iostream>
#include <vector>

using namespace std;

void print_adj_list(const vector <vector<int> >& g) {
    for (int v = 0; v < g.size(); ++v) {
        cout << v + 1 << ": ";
        for (int u : g[v]) {
            cout << u + 1 << " ";
        }
        cout << "\n";
    }
}

bool dfs(const int& v, vector<int>& color, const vector<vector<int> >& g, vector<int>& ans) {
    color[v] = 1;
    for (int u : g[v]) {
        if (!color[u]) {
            if (dfs(u, color, g, ans)) {
                return true;
            }
        }
        else if (color[u] == 1) {
            return true;
        }
    }
    color[v] = 2;
    ans.push_back(v);
    return false;
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
        // g[e].push_back(b);
    }
    // print adjacency list (for debug)
    // print_adj_list(g);
    // search for components in the graph
    vector<int> color(n, 0);
    vector<int> ans;
    for (int v = 0; v < n; ++v) {
        if (!color[v]) {
            if (dfs(v, color, g, ans)) {
                cout << -1;
                return 0;
            }
        }
    }
    // output (if no loop)
    for (int i = n - 1; i > -1; --i) {
        cout << ans[i] + 1 << " ";
    }
    return 0;
}

