#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int mod_2(const int& x, const int& pow_2) {
    return x - (x >> pow_2 << pow_2);
}
int mod(const int& x, const int& a) {
    return ((x % a) + a) % a;
}
long long rsq(const int& l, const int& r, const vector<long long>& sum) {
    if (l == 0) {
        return sum[r];
    }
    return sum[r] - sum[l - 1];
}
int main() {
    // input
    int n, x, y, a0;
    cin >> n >> x >> y >> a0;
    int m, z, t, b0;
    cin >> m >> z >> t >> b0;
    vector<long long> sum;
    vector<int> c;
    long long res = 0;

    // prefix sum array
    sum.push_back(a0);
    int prev = a0;
    for (int i = 1; i < n; ++i) {
        int ai = mod_2(x * prev + y,16);
        sum.push_back(sum[i - 1] + ai);
        prev = ai;
    }
    // queries array
    c.push_back(mod(b0, n));
    prev = b0;
    for (int i = 1; i < 2 * m; ++i) {
        int bi = mod_2(z * prev + t, 30);
        c.push_back(mod(bi, n));
        prev = bi;
    }
    // process queries
    for (int i = 0; i < m; ++i) {
        auto bounds = minmax(c[2 * i], c[(2 * i) + 1]);
        res += rsq(bounds.first, bounds.second, sum);
    }
    cout << res;
    return 0;
}
