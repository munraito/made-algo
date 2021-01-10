#include <iostream>
#include <vector>
using namespace std;

int bin_search(const vector<int>& v, int n, int k) {
	// find max element for right boundary
	int max_el = 0;
	for (int i : v) {
		if (i > max_el) {
			max_el = i;
		}
	}
	int left = 0;
	int right = max_el + 1;
	// start bin search
	while (left < (right - 1)) {
		int mid = (left + right) / 2;
		// count how much ropes can we make on each iteration
		int cnt = 0;
		for (int el : v) {
			cnt += el / mid;
		}
		// compare to number of houses
		if (cnt < k) {
			right = mid;
		} else {
			left = mid;
		}
	}
	return left;
}

int main() {
	ios::sync_with_stdio(false);
	// input
	int n, k;
	cin >> n >> k;
	vector<int> v;
	for (int i = 0; i < n; ++i) {
		int num;
		cin >> num;
		v.push_back(num);
	}
	// output
	cout << bin_search(v, n, k);
	return 0;
}

