#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

void count_sort(vector<int>& v) {
    //    initialize counter array ( +1 for all-zero case )
    int v_max = *max_element(v.begin(), v.end()) + 1;
    vector <int> cnt(v_max, 0);
    //    count frequency of each value
    for (int i = 0; i < v.size(); ++i) cnt[v[i]]++;
    //    change vector in-place
    int i = 0;
    for (int j = 0; j < v_max; ++j) {
        while (cnt[j] > 0) {
            v[i++] = j;
            cnt[j]--;
        }
    }
}

int main() {
    //    input
    vector<int> v;
    string input;
    getline(cin, input);
    stringstream iss(input);
    int num;
    while (iss >> num) v.push_back(num);
    //    sort
    count_sort(v);
    //    output
    for (int i : v) cout << i << " ";
    return 0;
}

