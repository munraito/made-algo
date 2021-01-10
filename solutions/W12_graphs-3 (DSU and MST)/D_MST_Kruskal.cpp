#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DSU {
public:
    explicit DSU(int n) {
        rank.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            parent.push_back(i);
        }
    }

    int get(int x) {
        if (parent[x] != x) {
            parent[x] = get(parent[x]);
        }
        return parent[x];
    }

    void join(int x, int y) {
        x = get(x);
        y = get(y);
        if (x != y) {
            if (rank[y] > rank[x]) {
                swap(x, y);
            }
            if (rank[x] == rank[y]) {
                rank[y]++;
            }
            parent[x] = y;
        }
    }

private:
    vector<int> parent, rank;
};

void kruskal_MST(const vector < pair < int, pair<int,int> > >& g, DSU& sets, int m) {
    long long ans = 0;
    int from, to, weight;
    for (int i = 0; i < m; ++i) {
        weight = g[i].first;
        from = g[i].second.first;
        to = g[i].second.second;
        if (sets.get(from) != sets.get(to)) {
            ans += weight;
            sets.join(from, to);
        }
    }
    cout << ans;
}

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    int n, m, from, to, weight;
    cin >> n >> m;
    // init DSU
    DSU sets(n);
    // init graph
    vector < pair < int, pair<int,int> > > g (m); // (weight, (from, to))
    for (int i = 0; i < m; ++i) {
        cin >> from >> to >> weight;
        from--;
        to--;
        g[i] = make_pair(weight, make_pair(from, to));
    }
    // sort edges by weights
    sort(begin(g), end(g));
    // compute MST, output
    kruskal_MST(g, sets, m);
    return 0;
}

