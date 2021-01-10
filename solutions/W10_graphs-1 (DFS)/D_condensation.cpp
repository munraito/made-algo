#include <iostream>
#include <vector>
#include <set>

using namespace std;

void print_adj_list(const vector <set<int> >& g) {
    for (int v = 0; v < g.size(); ++v) {
        cout << v + 1 << ": ";
        for (int u : g[v]) {
            cout << u + 1 << " ";
        }
        cout << "\n";
    }
}

void dfs_topological_sort(const int& v, vector<bool>& used, const vector<set<int> >& g, vector<int>& order) {
    used[v] = true;
    for (const int& u : g[v]) {
        if (!used[u]) {
            dfs_topological_sort(u, used, g, order);
        }
    }
    order.push_back(v);
}

void dfs_comp(const int& v, const vector<set<int> >& gr, const int cnt,  vector<int>& component) {
    component[v] = cnt;
    for (const int& u : gr[v]) {
        if (!component[u]) {
            dfs_comp(u, gr, cnt, component);
        }
    }
}

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout.tie(nullptr);
    // input
    int n, m, b, e;
    cin >> n >> m;
    vector <set<int> > g (n, set<int>());
    // reversed graph
    vector <set<int> > gr (n, set<int>());
    for (int i = 0; i < m; ++i) {
        cin >> b >> e;
        --b;
        --e;
        g[b].insert(e);
        gr[e].insert(b);
    }
    // print adjacency list (for debug)
    // print_adj_list(g);
    // topological sort of source graph
    vector<bool> used(n, false);
    vector<int> order;
    for (int v = 0; v < n; ++v) {
        if (!used[v]) {
            dfs_topological_sort(v, used, g, order);
        }
    }
    // find components in reversed graph
    vector<int> component(n, 0);
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        int v = order[n - i - 1];
        if (!component[v]) {
            ++cnt;
            dfs_comp(v, gr, cnt, component);
        }
    }
    // count edges between components
    int cnt_edges = 0;
    vector <set<int> > edges (cnt, set<int>());
    for (int v = 0; v < n; ++v) {
        for (const int& u : g[v]) {
            if (component[v] != component[u]) {
                edges[component[v] - 1].insert(component[u] - 1);
            }
        }
    }
    for (const auto& edge : edges) {
        cnt_edges += edge.size();
    }
    // output
    cout << cnt_edges;
    return 0;
}

