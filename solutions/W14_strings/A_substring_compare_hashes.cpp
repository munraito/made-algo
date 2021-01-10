#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int P = 67;
const int M = 100001227;

void init(const string& s, vector<long long>& hash, vector<long long>& pow_p) {
    hash[0] = s[0] - 'a' + 1; //  - 'a' + 1
    pow_p[0] = 1;
    for (int i = 1; i < s.length(); ++i) {
        hash[i] = (hash[i - 1] * P + (s[i] - 'a' + 1) + M) % M;
        pow_p[i] = ((pow_p[i - 1] * P) + M) % M;
    }
}

long long get_hash(int left, int right, const vector<long long>& hash, const vector<long long>& pow_p) {
    if (!left) {
        return hash[right];
    }
    return (hash[right] - (hash[left - 1] * pow_p[right - left + 1]) % M + M) % M;
}

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    string s;
    int m, a, b, c, d;
    cin >> s >> m;
    vector<long long> hash(s.length());
    vector<long long> pow_p(s.length());
    init(s, hash, pow_p);
    // process queries
    for (int i = 0; i < m; ++i) {
        cin >> a >> b >> c >> d;
        if (get_hash(a - 1, b - 1, hash, pow_p) == get_hash(c - 1, d - 1, hash, pow_p)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
