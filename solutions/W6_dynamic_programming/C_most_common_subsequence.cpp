#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

void solve(const vector<int>& v, int n) {
    vector<int> dp (n, 1);
    vector<int> p (n, -1);
    for (int i = 1; i < n; ++i) {
        for (int j = i - 1; j > -1; --j) {
            if ((v[j] < v[i]) && (dp[j] + 1 > dp[i])) {
                dp[i] = dp[j] + 1;
                p[i] = j;
            }
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << "\n";
    int i = max_element(dp.begin(), dp.end()) - dp.begin();
    vector<int> seq;
    // iterate over all parent indices
    while (i > -1) {
        seq.push_back(v[i]);
        i = p[i];
    }
    // output reverse sequence
    for (auto i = seq.rbegin(); i != seq.rend(); ++i ) {
        cout << *i << " ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    // input
    int n;
    cin >> n;
    vector<int> v (n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        v[i] = x;
    }
    // output
    solve(v, n);
    return 0;
}

