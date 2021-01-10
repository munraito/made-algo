#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

void solve(const vector<vector<int> >& coins, int n, int m) {
    vector<vector<int> > dp (n, vector<int> (m));
    vector<vector<pair<int, int> > > path (n, vector<pair<int, int> > (m));
    dp[0][0] = coins[0][0];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((i == 0) && (j > 0)) {
                dp[i][j] = dp[i][j - 1] + coins[i][j];
                path[i][j] = make_pair(i, j - 1);
            }
            if ((i > 0) && (j == 0)) {
                dp[i][j] = dp[i - 1][j] + coins[i][j];
                path[i][j] = make_pair(i - 1, j);
            }
            if ((i > 0) && (j > 0)) {
                if (dp[i][j - 1] >= dp[i - 1][j]) {
                    dp[i][j] = dp[i][j - 1] + coins[i][j];
                    path[i][j] = make_pair(i, j - 1);
                } else {
                    dp[i][j] = dp[i - 1][j] + coins[i][j];
                    path[i][j] = make_pair(i - 1, j);
                }
            }
        }
    }
    cout << dp[n - 1][m - 1] << "\n";
    int i = n - 1;
    int j = m - 1;
    int new_i;
    vector<char> ans;
    while ((i > 0) || (j > 0)) {
        new_i = path[i][j].first;
        if (new_i < i) {
            ans.push_back('D');
        } else {
            ans.push_back('R');
        }
        j = path[i][j].second;
        i = new_i;
    }
    reverse(ans.begin(), ans.end());
    for (char c: ans) {
        cout << c;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    // input
    int n, m;
    cin >> n >> m;
    vector<vector<int> > v (n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x;
            cin >> x;
            v[i][j] = x;
        }
    }
    // output
    solve(v, n, m);
    return 0;
}

