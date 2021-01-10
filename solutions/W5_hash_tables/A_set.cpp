#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// prime constants for hashing and memory
const int M = 1049219;
const int P = 1052083;

class Set {
public:
    int h(int x) {
        int res = (2 * x % P) % M;
        if (x < 0) {
            return -res;
        } else {
            return res;
        }
    }
    void insert(int x) {
        i = h(x);
        while ((arr[i].state != 0) && (arr[i].val != x)) {
            i = (i + 1) % M;
        }
        arr[i].val = x;
        arr[i].state = 1; // ok
    }
    void remove(int x) {
        i = h(x);
        while (arr[i].state != 0) {
            if (arr[i].val == x) {
                arr[i].state = 2; // rip
                break;
            }
            i = (i + 1) % M;
        }
    }
    string exists(int x) {
        i = h(x);
        while (arr[i].state != 0) {
            if ((arr[i].val == x) && (arr[i].state != 2)) {
                return "true";
            }
            i = (i + 1) % M;
        }
        return "false";
    }
private:
    struct element {
        int val;
        int state = 0;
    };
    element arr[M];
    int i;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    Set s;
    // input
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string q[2];
        iss >> q[0];
        iss >> q[1];
        if (q[0] == "insert") {
            s.insert(stoi(q[1]));
        } else if (q[0] == "delete") {
            s.remove(stoi(q[1]));
        } else if (q[0] == "exists") {
            cout << s.exists(stoi(q[1])) << "\n";
        }
    }
    return 0;
}

