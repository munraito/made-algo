#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int ALPHABET = 26;

int char_to_int(const char& c) {
    return (int)c - 97;
}

vector<string> radix_sort(vector<string>& input, int n, int m, const int& phases) {
    vector<string> output(n);
    //    radix phases loop, n - number of strings, m - size of each string
    for (int k = 0; k < phases; ++k) {
        //        initialize counter of letters
        vector<int> cnt(ALPHABET, 0);
        int curr = m - k - 1;
        //        counts of current letter
        for (auto str : input) cnt[char_to_int(str[curr])]++;
        //        calculate cumulative sum
        for (int i = 1; i < ALPHABET; ++i) cnt[i] += cnt[i - 1];
        //        rebuild array based on cumulative sum
        //        (each value in cnt is now an index of output array)
        for (int i = n - 1; i >= 0; --i) {
            string str = input[i];
            int out_i = cnt[char_to_int(str[curr])] - 1;
            output[out_i] = str;
            cnt[char_to_int(str[curr])]--;
        }
        //        copy output array to input
        //        now input will be sorted according to current phase
        input = output;
    }
    return output;
}

int main() {
    //    input
    vector<string> v;
    int n, m, phases;
    cin >> n >> m >> phases;
    string str;
    for (int i = 0; i < n; ++i) {
        cin >> str;
        v.push_back(str);
    }
    //    sort
    vector<string> out = radix_sort(v, n, m, phases);
    //    output
    for (auto i : out) cout << i << "\n";
    return 0;
}

