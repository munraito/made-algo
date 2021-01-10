#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> p_func(const string& s) {
    vector<int> p (s.length());
    p[0] = 0;
    for (int i = 1; i < s.length(); ++i) {
        int k = p[i - 1];
        while (k > 0 && s[i] != s[k]) {
            k = p[k - 1];
        }
        if (s[i] == s[k]) {
            k++;
        }
        p[i] = k;
    }
    return p;
}

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    string p, t;
    cin >> p >> t;
    // KMP
    string s = p + '#' + t;
    vector<int> pref = p_func(s);
    int count = 0;
    vector<int> ind;
    for (int i = 0; i < t.length(); ++i) {
        if (pref[i + p.length() + 1] == p.length()) {
            count++;
            ind.push_back(i - p.length() + 2);
        }
    }
    cout << count << "\n";
    for (int i : ind) {
        cout << i << " ";
    }

    return 0;
}

