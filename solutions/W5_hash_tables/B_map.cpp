#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

const int M = 1001941; // memory for array
const int P = 67; // prime > alphabet size * 2 (in case of capital letters)

class Map {
public:
    int h(string s) {
        int res = 0;
        int p_pow = 1;
        for (char c : s) {
            res = (res + (c - 'A' + 1) * p_pow) % M;
            p_pow = (p_pow * P) % M;
        }
        return res;
    }
    void put(string key, string val) {
        // update value
        bool found = false;
        for (auto& el : arr[h(key)]) {
            if (el.first == key) {
                el.second = val;
                found = true;
                break;
            }
        }
        // add new element
        if (!found) {
            arr[h(key)].push_back( make_pair(key, val) );
        }
    }
    void remove(string key) {
        auto& vec = arr[h(key)];
        for (int i = 0; i < vec.size(); ++i) {
            if (key == vec[i].first) {
                vec.erase(vec.begin() + i);
            }
        }
    }
    string get(string key) {
        for (auto el : arr[h(key)]) {
            if (el.first == key) {
                return el.second;
            }
        }
        return "none";
    }
private:
    vector<vector<pair<string, string>>> arr{M};
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    Map m;
    // input
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string q[3];
        iss >> q[0];
        iss >> q[1];
        if (q[0] == "put") {
            iss >> q[2];
            m.put(q[1], q[2]);
        } else if (q[0] == "delete") {
            m.remove(q[1]);
        } else if (q[0] == "get") {
            cout << m.get(q[1]) << "\n";
        }
    }
    return 0;
}

