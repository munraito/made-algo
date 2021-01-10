#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

const int ALPHABET = 26;

int char_to_int(const char& c) {
    return (int)c - 97;
}

long long find(const string& str, const string& cards) {
    long long sum = 0;
    //    counter of every card
    vector<int> cnt_cards(ALPHABET, 0);
    for (char c : cards) cnt_cards[char_to_int(c)]++;
    //    counter of str
    vector<int> cnt_str(ALPHABET, 0);
    //    window bounds and current index variables
    int left = 0, right = 0, i = 0;

    while (right < str.size()) {
        cnt_str[char_to_int(str[i])]++;
        //        check counter of cards vs counter of string
        int temp = 0;
        for (int i = 0; i < ALPHABET; ++i) {
            if (cnt_cards[i] >= cnt_str[i]) ++temp;
            else break;
        }
        if (temp == ALPHABET) {
            //        if counters match, add sum and expand the window
            sum += (right - left) + 1;
            ++right;
            i = right;
        }
        else {
            //        if counters doesn't match, then narrow the window
            cnt_str[char_to_int(str[left])]--;
            ++left;
            i = left;
            cnt_str[char_to_int(str[i])]--;
        }
    }
    return sum;
}

int main() {
    //    input
    int n, m;
    cin >> n >> m;
    string s, cards;
    cin >> s >> cards;
    //    output
    cout << find(s, cards) << "\n";
    return 0;
}

