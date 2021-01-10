#include <iostream>
#include <vector>
#include <set>

using namespace std;

void print_adj_list(const vector <set<int> >& g) {
    for (int v = 0; v < g.size(); ++v) {
        cout << v  << ": ";
        for (int u : g[v]) {
            cout << u  << " ";
        }
        cout << "\n";
    }
}

void dfs(const int& v, const vector<set<int> >& g, vector<bool>& used, vector<int>& tin,
         vector<int>& up, int& time, set<int>& cut_points, int parent = -1) {
    used[v] = true;
    tin[v] = up[v] = time++;
    int children = 0;
    for (const int& u : g[v]) {
        if (u == parent) {
            continue;
        } else if (used[u]) {
            up[v] = min(up[v], tin[u]);
        } else {
            dfs(u, g, used, tin, up, time, cut_points, v);
            up[v] = min(up[v], up[u]);
            if (up[u] >= tin[v] && parent != -1) {
                cut_points.insert(v);
            }
            ++children;
        }
    }
    if (parent == -1 && children > 1) {
        cut_points.insert(v);
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
    vector <set<int> > g (n, set<int>());
    for (int i = 0; i < m; ++i) {
        cin >> b >> e;
        --b;
        --e;
        g[b].insert(e);
        g[e].insert(b);
    }
    // print adjacency list (for debug)
    // print_adj_list(g);
    // find cut points
    vector<bool> used(n, false);
    set<int> cut_points;
    vector<int> tin(n, -1), up(n, -1);
    int time = 0;
    for (int v = 0; v < n; ++v) {
        if (!used[v]) {
            dfs(v, g, used, tin, up, time, cut_points);
        }
    }
    // output
    if (!cut_points.empty()) {
        cout << cut_points.size() << "\n";
        for (const int& cp : cut_points) {
            cout << cp + 1 << " ";
        }
    } else {
        cout << 0;
    }
    return 0;
}

