#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class BITree {
public:
    explicit BITree(const vector<long long>& v, int n) {
        // init with zeros
        this->n = n;
        bit.assign(n, 0);
        // then add vector values
        for (int i = 0; i < n; ++i) {
            add(i, v[i]);
        }
        // and copy its contents
        elements.assign(v.begin(), v.end());
    }
    void set(int i, long long x) {
        long long delta = x - elements[i];
        elements[i] = x;
        add(i, delta);
    }
    long long rsq(int l, int r) {
        if (l == 0) {
            return get(r);
        }
        return get(r) - get(l - 1);
    }
private:
    vector<long long> bit;
    vector<long long> elements;
    int n;
    void add(int i, long long x) {
        for (; i < n; i = i | (i + 1)) {
            bit[i] += x;
        }
    }
    long long get(int i) {
        long long res = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1) {
            res += bit[i];
        }
        return res;
    }
};

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    // input
    int n;
    cin >> n;
    vector<long long> v;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        v.push_back(x);
    }
    // init tree by input vector
    BITree bit(v, n);
    // process queries
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string q[3];
        for (auto & i : q) {
            iss >> i;
        }
        if (q[0] == "set") {
            int idx = stoi(q[1]) - 1;
            long long new_val = stoll(q[2]);
            bit.set(idx, new_val);
        } else if (q[0] == "sum") {
            int l = stoi(q[1]) - 1;
            int r = stoi(q[2]) - 1;
            cout << bit.rsq(l, r) << "\n";
        }
    }
    return 0;
}

