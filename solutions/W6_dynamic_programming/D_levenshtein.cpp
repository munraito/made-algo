#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int edit_dist(const string& s1, const string& s2) {
    int n = s1.length();
    int m = s2.length();
    int dp[n + 1][m + 1];
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i == 0) {
                // if first string is empty, insert all chars of second
                dp[i][j] = j;
            } else if (j == 0) {
                // if second string is empty, insert all chars of first
                dp[i][j] = i;
            } else if (s1[i - 1] == s2[j - 1]) {
                // if last chars equals, ignore them
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                // if last chars differ, get minimum of all 3 operations
                dp[i][j] = 1 + min( min(dp[i][j - 1],        // insert
                                        dp[i - 1][j]),       // remove
                                        dp[i - 1][j - 1] );  // replace
            }
        }
    }
    return dp[n][m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    // input
    string s1, s2;
    cin >> s1 >> s2;
    // output
    cout << edit_dist(s1, s2);
    return 0;
}

