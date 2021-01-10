#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

// iterations for search with 1e-6 precision
const int ITN = 60;

double bin_search(double c, double left, double right) {
	// binary search for float function
	for (int i = 0; i < ITN; ++i) {
		double mid = (left + right) / 2;
		if (mid*mid + sqrt(mid) < c) {
			left = mid;
		} else {
			right = mid;
		}
	}
	return right;
}

int main() {
	// input
	double c;
	cin >> c;
	double sqrt_c = sqrt(c);
	// output
	cout << setprecision(7) << bin_search(c, sqrt_c - 1, sqrt_c + 1);
	return 0;
}

