#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int lower_bound(const vector<int>& v, int q, int n) {
	int left = -1;
	int right = n;
	while (left < (right - 1)) {
		int mid = (left + right) / 2;
		if (q <= v[mid]) {
			right = mid;
		} else {
			left = mid;
		}
	}
	// return index
	return right;
}

int cnt_interval(const vector<int>& v, int l, int r, int n) {
	// upper - lower
	return lower_bound(v, r + 1, n) - lower_bound(v, l, n);
}

int main() {
	ios::sync_with_stdio(false);
	// input array
	int n, k;
	vector<int> v;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int num;
		cin >> num;
		v.push_back(num);
	}
	// sort array
	sort(v.begin(), v.end());
	// queries
	cin >> k;
	for (int i = 0; i < k; ++i) {
		int l, r;
		cin >> l >> r;
		cout << cnt_interval(v, l, r, n) << " ";
	}
	return 0;
}

