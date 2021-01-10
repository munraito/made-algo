#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node (int k) {
        key = k;
        left = right = nullptr;
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
        if (v == nullptr) {
            // init root
            v = new Node(x);
        } else if (x < v->key) {
            v->left = insert(v->left, x);
        } else if (x > v->key) {
            v->right = insert(v->right, x);
        }
        return v;
    }
    Node* remove(Node* v, int x) {
        // remove leaf
        if (!v) {
            return v;
        }
        if (x < v->key) {
            v->left = remove(v->left, x);
        } else if (x > v->key) {
            v->right = remove(v->right, x);
        } else {
            // remove node
            // node with one or without children
            if (v->left == nullptr) {
                Node* temp = v->right;
                delete v;
                v = temp;
            } else if (v->right == nullptr) {
                Node* temp = v->left;
                delete v;
                v = temp;
            } else {
                // node with two children
                v->key = find_max(v->left)->key;
                v->left = remove(v->left, v->key);
            }
        }
        return v;
    }
    string next(int x) {
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
    string prev(int x) {
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
    Node* find_max(Node* v) {
        while (v->right) {
            v = v->right;
        }
        return v;
    }
    Node* search(Node* v, int x) {
        if (!v) {
            // base case
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
	
