#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

const int P = 67;
const int M = 100001227;

void init(const string& s, vector<long long>& hash, vector<long long>& pow_p) {
    hash[0] = s[0] - 'a' + 1;
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

string find_lcs(vector<string>& str) {
    // init hashes for all strings
    vector<vector<long long>> all_hashes;
    vector<vector<long long>> all_powers;
    int min_len = 10001;
    int min_i;
    for (int i = 0; i < str.size(); ++i) {
        vector<long long> curr_hash(str[i].length());
        vector<long long> curr_pow(str[i].length());
        init(str[i], curr_hash, curr_pow);
        all_hashes.push_back(curr_hash);
        all_powers.push_back(curr_pow);
        if (str[i].length() < min_len) {
            min_len = str[i].length();
            min_i = i;
        }
    }
    // determine base str (with min length)
    string base_str = str[min_i];
    vector<long long> base_hash = all_hashes[min_i];
    vector<long long> base_pow = all_powers[min_i];
    str.erase(str.begin() + min_i);
    all_hashes.erase(all_hashes.begin() + min_i);
    all_powers.erase(all_powers.begin() + min_i);
    // run bin search on base str vs others
    int l = 0;
    int r = min_len;
    int pos = -1;
    while (r >= l) {
        int mid = l + (r - l) / 2;
        // store all occurrences of hashes of current length in map of sets
        map<long long, set<int> > curr_hashes;
        for (int i = 0; i < all_hashes.size(); ++i) {
            for (int j = 0; j + mid <= str[i].length(); ++j) {
                curr_hashes[get_hash(j, j + mid - 1, all_hashes[i], all_powers[i])].insert(i);
            }
        }
        // compare to hashes of base string
        int p = -1;
        for (int i = 0; i + mid <= base_str.length(); ++i) {
            long long curr_base_hash = get_hash(i, i + mid - 1, base_hash, base_pow);
            // check if substring from base exists in every other string
            if (curr_hashes[curr_base_hash].size() == all_hashes.size()) {
                p = i;
                break;
            }
        }
        if (p > -1) {
            l = mid + 1;
            pos = p;
        } else {
            r = mid - 1;
        }
    }
    if (pos > -1) {
        return base_str.substr(pos, l - 1);
    } else {
        return "";
    }
}

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // input
    int k;
    cin >> k;
    vector<string> str;
    for (int i = 0; i < k; ++i) {
        string s;
        cin >> s;
        str.push_back(s);
    }
    // output
    cout << find_lcs(str);
    return 0;
}

