#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

struct Point {
    int x;
    int y;
    Point(int x, int y) : x(x), y(y) { }
};

double euclidian_dist(const Point& p, const Point& q) {
    double dx = (p.x - q.x);
    double dy = (p.y - q.y);
    return dx*dx + dy*dy;
}

void prim_MST(const vector<Point>& g, int n) {
    vector<bool> used(n, false);
    vector<double> min_weight(n, INT_MAX);
    min_weight[0] = 0;
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || min_weight[j] < min_weight[v]) ) {
                v = j;
            }
        }
        used[v] = true;
        if (min_weight[v] != INT_MAX) {
            ans += sqrt(min_weight[v]);
        }
        for (int u = 0; u < n; ++u) {
            double dist2 = euclidian_dist(g[v], g[u]);
            min_weight[u] = min(dist2, min_weight[u]);
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
    int n, x, y;
    cin >> n;
    // init graph
    vector<Point> g;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        g.emplace_back(x, y);
    }
    // compute MST, output
    prim_MST(g, n);
    return 0;
}

