#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
const int M = 101939; // size of array
const int P = 67; // prime > alphabet size * 2 (in case of capital letters)

class Map {
public:
    void put(const string& key, const string& val) {
        // update value
        bool found = false;
        for (auto& el : arr[h(key)]) {
            if (el->key == key) {
                el->val = val;
                found = true;
                //also update links
                if (el->next != nullptr) {
                    el->next->prev->val = val;
                }
                if (el->prev != nullptr) {
                    el->prev->next->val = val;
                }
                break;
            }
        }
        // add new element
        if (!found) {
            Node* temp = new Node;
            temp->key = key;
            temp->val = val;

            // update links
            Node* last = head;
            if (head == nullptr) {
                // first node case
                head = temp;
            }
            else {
                // append to the end
                while (last->next != nullptr) {
                    last = last->next;
                }
                last->next = temp;
                temp->prev = last;
            }
            arr[h(key)].push_back(temp);
        }
    }
    void remove(const string& key) {
        int i = 0;
        for(auto& el : arr[h(key)]) {
            if (key == el->key) {
                // delete links
                // if head node
                if (el->prev == nullptr) {
                    head = el->next;
                }
                // change next only if node to be deleted is NOT the last node
                if (el->next != nullptr) {
                    el->next->prev = el->prev;
                }
                // change prev only if node to be deleted is NOT the first node
                if (el->prev != nullptr) {
                    el->prev->next = el->next;
                }
                // delete element itself
                arr[h(key)].erase(arr[h(key)].begin() + i);
                break;
            }
            ++i;
        }
    }
    string get(const string& key, const int& operation) {
        // operation: 0 - get curr, 1 - get prev, 2 - get next
        for (auto el : arr[h(key)]) {
            if (el->key == key) {
                if (operation == 0) {
                    return el->val;
                }
                else if (operation == 1 && el->prev != nullptr) {
                    return el->prev->val;
                }
                else if (operation == 2 && el->next != nullptr) {
                    return el->next->val;
                }
            }
        }
        return "none";
    }

private:
    struct Node {
        string key;
        string val;
        Node* next = nullptr;
        Node* prev = nullptr;
    };
    Node* head = nullptr;
    vector <vector<Node*>> arr{ M };
    
    static int h(const string& s) {
        int res = 0;
        int p_pow = 1;
        for (char c : s) {
            res = (res + (c - 'A' + 1) * p_pow) % M;
            p_pow = (p_pow * P) % M;
        }
        return res;
    }
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
        }
        else if (q[0] == "delete") {
            m.remove(q[1]);
        }
        else if (q[0] == "get") {
            cout << m.get(q[1], 0) << "\n";
        }
        else if (q[0] == "prev") {
            cout << m.get(q[1], 1) << "\n";
        }
        else if (q[0] == "next") {
            cout << m.get(q[1], 2) << "\n";
        }
    }
    return 0;
}
