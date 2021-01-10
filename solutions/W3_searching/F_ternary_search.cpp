#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

// iterations for search with 1e-6 precision 
const int ITN = 60;

double tp(double a, int V, double x) {
	//time for moving in the field
	return sqrt((1 - a) * (1 - a) + x * x) / V;
}

double tf(double a, int V, double x) {
	//time for moving in the forest
	return sqrt((1 - x) * (1 - x) + a * a) / V;
}

double ternary_search(int Vp, int Vf, double a) {
	double left = 0.0001;
	double right = 0.9999;
	for (int i = 0; i < ITN; ++i) {
		double m1 = (left * 2 + right) / 3;
		double m2 = (left + right * 2) / 3;
		// compare total times of two coordinates
		if (tp(a, Vp, m1) + tf(a, Vf, m1) < tp(a, Vp, m2) + tf(a, Vf, m2)) {
			right = m2;
		} else {
			left = m1;
		}
	}
	return (left + right) / 2;
}

int main() {
	// input
	int Vp, Vf;
	double a;
	cin >> Vp >> Vf >> a;
	// output
	cout << setprecision(5) << ternary_search(Vp, Vf, a);
	return 0;
}

