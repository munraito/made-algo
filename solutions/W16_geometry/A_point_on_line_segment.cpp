#include <iostream>
using namespace std;

struct Point {
    int x;
    int y;
    Point(const int& x, const int& y): x(x), y(y) {
    }
};

class Vector {
public:
    int x;
    int y;
    Vector (Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

int cross_product(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int dot_product(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

bool is_inside(Point p, Point a, Point b) {
    Vector ab(a, b), ap(a, p), bp(b, p);
    if (cross_product(ab, ap) != 0) {
        return false;
    }
    if (dot_product(ap, bp) > 0) {
        return false;
    }
    return true;
}

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    int px, py, ax, ay, bx, by;
    cin >> px >> py >> ax >> ay >> bx >> by ;
    if ( is_inside(Point(px, py), Point(ax, ay), Point(bx, by)) ) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
