#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class DSU {
public:
    explicit DSU(int n) {
        rank.assign(n, 0);
        count_el.assign(n, 1);
        for (int i = 0; i < n; ++i) {
            parent.push_back(i);
            max_el.push_back(i + 1);
            min_el.push_back(i + 1);
        }
    }

    void print_get(int x) {
        x = get(x);
        cout << min_el[x] << " " << max_el[x] << " " << count_el[x] << "\n";
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
        if (x == y) {
            return;
        }
        if (rank[x] > rank[y]) {
            swap(x, y);
        }
        if (rank[x] == rank[y]) {
            rank[y]++;
        }
        parent[x] = y;
        max_el[y] = max(max_el[x], max_el[y]);
        min_el[y] = min(min_el[x], min_el[y]);
        count_el[y] += count_el[x];
    }

private:
    vector<int> parent, rank, count_el, max_el, min_el;
};

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    int n;
    cin >> n;
    DSU sets(n);
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<string> v;
        for (string s; iss >> s; ) {
            v.push_back(s);
        }
        if (v.size() < 2) {
            continue;
        } else if (v[0] == "union") {
            sets.join(stoi(v[1]) - 1, stoi(v[2]) - 1);
        } else if (v[0] == "get") {
            sets.print_get(stoi(v[1]) - 1);
        }
    }
    return 0;
}

