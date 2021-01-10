#include <iostream>
using namespace std;

int bin_search(int n, int x, int y) {
	int min_el = x < y ? x : y;
	long long left = min_el - 1;
	long long right = min_el * n;
	while (left < (right - 1)) {
		long long mid = (left + right) / 2;
		// count how much copies can we make in the current moment
		long long cnt = 1 + ((mid - min_el) / x) + ((mid - min_el) / y);
		// compare it to the answer
		if (cnt >= n) {
			right = mid;
		} else {
			left = mid;
		}
	}
	return right;
}

int main() {
	// input
	int n, x, y;
	cin >> n >> x >> y;
	cout << bin_search(n, x, y);
	// output
	return 0;
}

