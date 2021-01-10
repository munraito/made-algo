#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(const vector<int>& v, int k) {
    vector<int> dp;
    vector<int> jumps;
    // add base points
    dp.push_back(v[0]);
    jumps.push_back(1);
    vector<int>::iterator max_el;
    int max_ind;
    for (int i = 1; i < v.size(); ++i) {
        if (i - k >= 0) {
            max_el = max_element(dp.begin() + (i - k), dp.begin() + i);
        } else {
            max_el = max_element(dp.begin(), dp.begin() + i);
        }
        max_ind = max_el - dp.begin() + 1;
        if (max_ind != jumps.back()) {
            jumps.push_back(max_ind);
        }
        dp.push_back(*max_el + v[i]);
    }
    // add final point
    jumps.push_back(v.size());
    // print result
    cout << dp.back() << "\n";
    cout << jumps.size() - 1 << "\n";
    for (int j : jumps) {
        cout << j << " ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    // input
    int n, k;
    cin >> n >> k;
    vector<int> v;
    v.push_back(0); // 0 coins at the start
    for (int i = 0; i < n - 2; ++i) {
        int x;
        cin >> x;
        v.push_back(x);
    }
    v.push_back(0); // and 0 at the end
    // output
    solve(v, k);
    return 0;
}

