#include <iostream>

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

int sign(int x) {
    if (x > 0) {
        return 1;
    } else if (x < 0) {
        return -1;
    }
    return 0;
}

int cross_product(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int dot_product(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

bool point_on_segment(Point p, Point a, Point b) {
    Vector ab(a, b), ap(a, p), bp(b, p);
    if (cross_product(ab, ap) != 0) {
        return false;
    }
    if (dot_product(ap, bp) > 0) {
        return false;
    }
    return true;
}

bool segment_intersects(Point a, Point b, Point c, Point d) {
    Vector ab(a, b), cd(c, d), ac(a, c), ad(a, d), ca(c, a), cb(c, b);
    int cp1 = sign(cross_product(ab, ac));
    int cp2 = sign(cross_product(ab, ad));
    int cp3 = sign(cross_product(cd, ca));
    int cp4 = sign(cross_product(cd, cb));
    if (!cp1 && !cp2 && !cp3 && !cp4) {
        return ( point_on_segment(a, c, d) || point_on_segment(b, c, d) ||
                point_on_segment(c, a, b) || point_on_segment(d, a, b) );
    }
    return (cp1 != cp2 && cp3 != cp4);
}

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    int ax, ay, bx, by, cx, cy, dx, dy;
    cin >> ax >> ay >> bx >> by >> cx >> cy >> dx >> dy;
    // output
    if ( segment_intersects(Point(ax, ay), Point(bx, by), Point(cx, cy), Point(dx, dy)) ) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}

