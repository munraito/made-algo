#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    int key;
    unsigned char height;
    Node* left;
    Node* right;
    Node (int k) {
        key = k;
        left = right = nullptr;
        height = 1;
    }
};
class BST {
public:
    Node* root;
    BST() {
        // init empty tree
        root = nullptr;
    }
    void print(Node* v, string indent) {
        if (v) {
            print(v->left, indent + "  ");
            cout << indent << v->key << "\n";
            print(v->right, indent + "  ");
        }
    }
    string exists(Node* v, int x) {
        // search for key starting from the root
        if (search(v, x) == nullptr) {
            return "false";
        } else {
            return "true";
        }
    }
    Node* insert(Node* v, int x) {
        // search for right place and insert
        if (v == nullptr) {
            v = new Node(x);
        } else if (x < v->key) {
            v->left = insert(v->left, x);
        } else if (x > v->key) {
            v->right = insert(v->right, x);
        }
        return balance(v);
    }
    Node* remove(Node* v, int x) {
        if (!v) {
            return v;
        }
        if (x < v->key) {
            v->left = remove(v->left, x);
        } else if (x > v->key) {
            v->right = remove(v->right, x);
        } else {
            // found node
            Node* l = v->left;
            Node* r = v->right;
            delete v;
            if (!r) {
                return l;
            }
            Node* min = find_min(r);
            min->right = remove_min(r);
            min->left = l;
            return balance(min);
        }
        return balance(v);
    }
    string next(int x) const {
        Node* v = root;
        Node* res = nullptr;
        while (v) {
            if (v->key > x) {
                res = v;
                v = v->left;
            } else {
                v = v->right;
            }
        }
        return res ? to_string(res->key) : "none";
    }
    string prev(int x) const {
        Node* v = root;
        Node* res = nullptr;
        while (v) {
            if (v->key < x) {
                res = v;
                v = v->right;
            } else {
                v = v->left;
            }
        }
        return res ? to_string(res->key) : "none";
    }
private:
    unsigned char get_height(Node* v) {
        return v ? v->height : 0;
    }
    int get_balance_ratio(Node* v) {
        return get_height(v->right) - get_height(v->left);
    }
    void fix_height(Node* v) {
        unsigned char h_l = get_height(v->left);
        unsigned char h_r = get_height(v->right);
        v->height = (h_l > h_r ? h_l : h_r) + 1;
    }
    Node* rotate_left(Node* q) {
        Node* p = q->right;
        q->right = p->left;
        p->left = q;
        fix_height(p);
        fix_height(q);
        return p;
    }
    Node* rotate_right(Node* p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        fix_height(p);
        fix_height(q);
        return q;
    }
    Node* balance(Node* v) {
        fix_height(v);
        if (get_balance_ratio(v) == 2) {
            if (get_balance_ratio(v->right) < 0) {
                v->right = rotate_right(v->right);
            }
            return rotate_left(v);
        }
        if (get_balance_ratio(v) == -2) {
            if (get_balance_ratio(v->left) > 0) {
                v->left = rotate_left(v->left);
            }
            return rotate_right(v);
        }
        return v;
    }
    Node* find_min(Node* v) {
        while (v->left) {
            v = v->left;
        }
        return v;
    }
    Node* remove_min(Node* v) {
        if (!v->left) {
            return v->right;
        }
        v->left = remove_min(v->left);
        return balance(v);
    }
    Node* search(Node* v, int x) {
        if (!v) {
            return v;
        }
        if (v->key == x) {
            return v;
        } else if (x < v->key) {
            return search(v->left, x);
        } else {
            return search(v->right, x);
        }
    }
};

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // input
    BST tree;
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        vector<string> v;
        for (string s; iss >> s; ) {
            v.push_back(s);
        }
        if (v[0] == "insert") {
            tree.root = tree.insert(tree.root, stoi(v[1]));
            // tree.print(tree.root, "");
        } else if (v[0] == "delete") {
            tree.root = tree.remove(tree.root, stoi(v[1]));
            // tree.print(tree.root, "");
        } else if (v[0] == "exists") {
            cout << tree.exists(tree.root, stoi(v[1])) << "\n";
        } else if (v[0] == "next") {
             cout << tree.next(stoi(v[1])) << "\n";
        } else if (v[0] == "prev") {
             cout << tree.prev(stoi(v[1])) << "\n";
        }
    }
    return 0;
}

