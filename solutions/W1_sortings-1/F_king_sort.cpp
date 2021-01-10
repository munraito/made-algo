#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;
 
void PrintMap(const map<string, vector<string> >& m) {
    for (auto item : m) {
        for (auto num : item.second) {
            cout << item.first << " " << num << endl;
        }
    }
}
int RomanToInt(const string& roman) {
    map<char, int> rmap;
    rmap['I'] = 1;
    rmap['V'] = 5;
    rmap['X'] = 10;
    rmap['L'] = 50;
    int res = 0;
 
    for (int i = 0; i < roman.size(); ++i) {
        int s1 = rmap[roman[i]];  // curr symbol
        if (i + 1 < roman.size()) {
            int s2 = rmap[roman[i + 1]];  // next symbol
            if (s1 >= s2) {
                res += s1;  // add current if it's greater than next
            } else {
                res += s2 - s1;  // for cases like 'IX', 'IV', etc.
                ++i;  // and skip next symbol
            }
        } else {
            res += s1;  // if this is the last symbol in sequence
        }
    }
    return res;
}
bool CompareRoman(const string& s1, const string& s2) {
    return RomanToInt(s1) < RomanToInt(s2);
}
 
int main() {
    // input
    int N;
    cin >> N;
    map <string, vector<string> > kings;
    for (int i = 0; i < N; ++i) {
        string name, num;
        cin >> name >> num;
        kings[name].push_back(num);
    }
 
    // sort
    for (auto& item : kings) {
        sort(item.second.begin(), item.second.end(), CompareRoman);
    }
 
    // output
    PrintMap(kings);
 
    return 0;
}

