#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int x;
    int y;
    Node* left;
    Node* right;
    Node(int key) {
        x = key;
        // random value for y
        y = rand();
        left = right = nullptr;
    }
};

class Treap {
public:
    Node* root;
    Treap() {
        // init empty tree
        root = nullptr;
    }
    void print(Node* v, string indent) {
        if (v) {
            print(v->left, indent + "  ");
            cout << indent << v->x << ", " << v->y << "\n";
            print(v->right, indent + "  ");
        }
    }
    string exists(Node* v, int x) {
        // search for key starting from the root
        if (!search(v, x)) {
            return "false";
        }
        else {
            return "true";
        }
    }
    Node* insert(Node* v, int x) {
        Node* t1, * t2;
        if (search(v, x)) {
            // if key is already in treap, do nothing
            return v;
        }
        split(v, x, t1, t2);
        merge(t1, t1, new Node(x));
        merge(v, t1, t2);
        return v;
    }
    Node* remove(Node* v, int x) {
        Node* t1, * t2, * t11, * t12;
        split(v, x, t1, t2);
        split(t1, x - 1, t11, t12);
        merge(v, t11, t2);
        return v;
    }
    string next(int x) {
        Node* v = root;
        Node* res = nullptr;
        while (v) {
            if (v->x > x) {
                res = v;
                v = v->left;
            }
            else {
                v = v->right;
            }
        }
        return res ? to_string(res->x) : "none";
    }
    string prev(int x) {
        Node* v = root;
        Node* res = nullptr;
        while (v) {
            if (v->x < x) {
                res = v;
                v = v->right;
            }
            else {
                v = v->left;
            }
        }
        return res ? to_string(res->x) : "none";
    }
private:
    void split(Node* v, int x, Node*& t1, Node*& t2) {
        if (!v) {
            t1 = t2 = nullptr;
        }
        else if (v->x > x) {
            split(v->left, x, t1, v->left);
            t2 = v;
        }
        else {
            split(v->right, x, v->right, t2);
            t1 = v;
        }
    }
    void merge(Node*& v, Node* t1, Node* t2) {
        if (!t1 || !t2) {
            v = t1 ? t1 : t2;
        }
        else if (t1->y > t2->y) {
            merge(t1->right, t1->right, t2);
            v = t1;
        }
        else {
            merge(t2->left, t1, t2->left);
            v = t2;
        }
    }
    Node* search(Node* v, int x) {
        if (!v) {
            // base case
            return v;
        }
        if (v->x == x) {
            return v;
        }
        else if (x < v->x) {
            return search(v->left, x);
        }
        else {
            return search(v->right, x);
        }
    }
};

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // input
    Treap tree;
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
        }
        else if (v[0] == "delete") {
            tree.root = tree.remove(tree.root, stoi(v[1]));
            // tree.print(tree.root, "");
        }
        else if (v[0] == "exists") {
            cout << tree.exists(tree.root, stoi(v[1])) << "\n";
        }
        else if (v[0] == "next") {
            cout << tree.next(stoi(v[1])) << "\n";
        }
        else if (v[0] == "prev") {
            cout << tree.prev(stoi(v[1])) << "\n";
        }
    }
    return 0;
}

