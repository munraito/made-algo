#include <iostream>
#include <vector>
using namespace std;

int bin_search(const vector<int>& v, int q, int n) {
	// classical bin search, but updated upper boundary
	// to prevent accessing n + 1 element of vector
	int left = -1;
	int right = n - 1;
	while (left < (right - 1)) {
		int mid = (left + right) / 2; 
		// comparing difference of neighboring elements
		if ( (q - v[mid] <= v[mid + 1] - q) ) {
			right = mid;
		}
		else {
			left = mid;
		}
	}
	return v[right];
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
	// queries
	for (int i = 0; i < k; ++i) {
		int q;
		cin >> q;
		cout << bin_search(v, q, n) << "\n";
	}
	return 0;
}

