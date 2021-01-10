#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class DSU {
public:
    explicit DSU(int n) {
        rank.assign(n, 0);
        exp.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            parent.push_back(i);
        }
    }

    void get_exp(int x) {
        if (x == parent[x]) {
            cout << exp[x] << "\n";
        } else {
            cout << exp[get(x)] + exp[x] << "\n";
        }
    }

    int get(int x) {
        if (parent[x] != x) {
            int prev_parent = parent[x];
            parent[x] = get(parent[x]);
            if (parent[x] != prev_parent) {
                exp[x] += exp[prev_parent];
            }
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
            exp[x] -= exp[y];
        }
    }

    void add(int x, int v) {
        exp[get(x)] += v;
    }
private:
    vector<int> parent, rank, exp;
};

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    int n, m;
    cin >> n >> m;
    DSU sets(n);
    for (int i = 0; i < m; ++i) {
        string operation;
        int x, y;
        cin >> operation;
        if (operation == "join") {
            cin >> x >> y;
            sets.join(x - 1, y - 1);
        } else if (operation == "add") {
            cin >> x >> y;
            sets.add(x - 1, y);
        } else if (operation == "get") {
            cin >> x;
            sets.get_exp(x - 1);
        }
    }
    return 0;
}

