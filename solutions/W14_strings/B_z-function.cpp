#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> z_func(const string& s) {
    vector<int> z(s.length());
    int left = 0;
    int right = 0;
    for (int i = 1; i < s.length(); ++i) {
        z[i] = max(0, min(right - i, z[i - left]));
        while (i + z[i] < s.length() && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > right) {
            left = i;
            right = i + z[i];
        }
    }
    return z;
}

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    string s;
    cin >> s;
    vector<int> z = z_func(s);
    for (int i = 1; i < s.length(); ++i) {
        cout << z[i] << " ";
    }
    return 0;
}

