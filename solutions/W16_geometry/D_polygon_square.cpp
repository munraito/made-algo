#include <iostream>
#include <vector>

using namespace std;

struct Point {
    int x;
    int y;
    Point(const int& x, const int& y): x(x), y(y) {
    }
};

struct Vector {
    int x;
    int y;
    Vector (const Point& a, const Point& b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

int cross_product(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

double polygon_square(const vector<Point>& poly) {
    double sq = 0;
    for (int i = 1; i < poly.size() - 1; ++i) {
        Vector p0pi(poly[0], poly[i]), p0pi_next(poly[0], poly[i + 1]);
        sq += cross_product(p0pi, p0pi_next);
    }
    return abs(sq / 2.0);
}

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    int n;
    cin >> n;
    vector<Point> poly;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        poly.emplace_back(x, y);
    }
    // output
    cout << polygon_square(poly);
    return 0;
}

