#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    // input
    int n, m, ai, ui, vi;
    cin >> n >> m >> ai >> ui >> vi;
    // build source array
    int a[n];
    a[0] = ai;
    for (int i = 1; i < n; ++i) {
        a[i] = (23 * ai + 21563) % 16714589;
        ai = a[i];
    }
    // precompute logarithms for latter use
    int log[n+1];
    log[1] = 0;
    for (int i = 2; i <= n; i++) {
        log[i] = log[i/2] + 1;
    }
    // build sparse table
    int k = log[n] + 1;
    int st [n][k];
    // base
    for (int i = 0; i < n; ++i) {
        st[i][0] = a[i];
    }
    // rest, from smaller to bigger
    for (int j = 1; j <= k; ++j) {
        // compute min for all ranges with size 2^j
        for (int i = 0; i + (1 << j) <= n; ++i) {
            st[i][j] = min(st[i][j - 1],
                           st[i + (1 << (j - 1))][j - 1]);
        }
    }
    // process queries, first step
    auto bounds_i = minmax(ui, vi);
    int j = log[bounds_i.second - bounds_i.first + 1];
    int ri = min(st[bounds_i.first - 1][j],
                 st[bounds_i.second - (1 << j)][j]);
    // next steps
    for (int i = 2; i <= m; ++i) {
        ui = ((17*ui + 751 + ri + 2*(i - 1)) % n) + 1;
        vi = ((13*vi + 593 + ri + 5*(i - 1)) % n) + 1;
        auto bounds_i = minmax(ui, vi);
        j = log[bounds_i.second - bounds_i.first + 1];
        ri = min(st[bounds_i.first - 1][j],
                 st[bounds_i.second - (1 << j)][j]);
    }
    cout << ui << " " << vi << " " << ri;
    return 0;
}

