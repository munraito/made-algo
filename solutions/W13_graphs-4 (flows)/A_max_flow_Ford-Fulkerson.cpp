#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge{
    int to;
    int cap;
    int flow;
    int link;
    Edge(int to, int cap, int flow, int link) : to(to), cap(cap), flow(flow), link(link) { }
};

int push_flow(int v, int t, int curr_flow, vector <vector<Edge> >& g, vector<bool>& used) {
    used[v] = true;
    if (v == t) {
        return curr_flow;
    }
    for (auto& edge : g[v]) {
        int next_flow, delta;
        if (!used[edge.to] && edge.flow < edge.cap) {
            next_flow = min(curr_flow, edge.cap - edge.flow);
            delta = push_flow(edge.to, t, next_flow, g, used);
            if (delta > 0) {
                edge.flow += delta;
                g[edge.to][edge.link].flow -= delta;
                return delta;
            }
        }
    }
    return 0;
}

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    int n, m, from, to, capacity;
    cin >> n >> m;
    vector <vector<Edge> > g (n, vector<Edge>());
    for (int i = 0; i < m; ++i) {
        cin >> from >> to >> capacity;
        --from;
        --to;
        g[from].push_back(Edge(to, capacity, 0, g[to].size()));
        g[to].push_back(Edge(from, capacity, 0, g[from].size() - 1));
    }
    vector<bool> used (n);
    int delta;
    int ans = 0;
    while (true) {
        used.assign(n, false);
        delta = push_flow(0, n - 1, INT_MAX, g, used);
        // cout << delta << "\n";
        if (delta > 0) {
            ans += delta;
        } else {
            break;
        }
    }
    cout << ans;
    return 0;
}

