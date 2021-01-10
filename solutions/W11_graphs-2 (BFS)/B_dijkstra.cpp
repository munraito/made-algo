#include <iostream>
#include <climits>
#include <set>
#include <vector>

using namespace std;

void dijkstra_shortest_path(const vector <vector<pair<int,int>> >& g, int n) {
    int start = 0;
    vector<unsigned long long> dist(n, ULONG_LONG_MAX);
    set<pair<int,int> > q;
    dist[start] = 0;
    q.insert(make_pair(dist[start], start));
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto i : g[v]) {
            int u = i.first, weight = i.second;
            if (dist[u] > dist[v] + weight){
                q.erase(make_pair(dist[u], u));
                dist[u] = dist[v] + weight;
                q.insert(make_pair(dist[u], u));
            }
        }
    }
    for (auto d : dist) {
        cout << d << " ";
    }
}

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    int n, m, from, to, weight;
    cin >> n >> m;
    vector <vector<pair<int,int>> > g (n, vector<pair<int,int>>());
    for (int i = 0; i < m; ++i) {
        cin >> from >> to >> weight;
        from--;
        to--;
        g[from].push_back(make_pair(to, weight));
        g[to].push_back(make_pair(from, weight));
    }
    dijkstra_shortest_path(g, n);
    return 0;
}

