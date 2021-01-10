#include <iostream>

using namespace std;

struct Node {
    int el;
    int size;
    int y;
    bool rev;
    Node* left;
    Node* right;
    Node(int val) {
        el = val;
        size = 1;
        rev = false;
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
    void print(Node* v) {
        if (v) {
            push(v);
            print(v->left);
            cout << v->el << " ";
            print(v->right);
        }
    }
    Node* reverse(Node* v, int l, int r) {
        Node* t1, * t2, * t3;
        split(v, l, t1, t2);
        split(t2, r - l, t2, t3);
        t2->rev ^= true;
        merge(v, t1, t2);
        merge(v, v, t3);
        return v;
    }
    Node* add(Node* v, int pos, int x) {
        Node* t1, * t2;
        split(v, pos, t1, t2);
        merge(t1, t1, new Node(x));
        merge(v, t1, t2);
        return v;
    }
private:
    void push(Node*& v) {
        if (v && v->rev) {
            // swap current vertex
            v->rev = false;
            Node* temp = v->left;
            v->left = v->right;
            v->right = temp;
            // change promise for children
            if (v->left) {
                v->left->rev ^= true;
            }
            if (v->right) {
                v->right->rev ^= true;
            }
        }
    }
    int get_size(Node* v) {
        return v ? v->size : 0;
    }
    void fix(Node* v) {
        if (v) {
            v->size = get_size(v->left) + 1 + get_size(v->right);
        }
    }
    void split(Node* v, int x, Node*& t1, Node*& t2) {
        push(v);
        if (!v) {
            t1 = t2 = nullptr;
            return;
        }
        if (get_size(v->left) > x) {
            split(v->left, x, t1, v->left);
            t2 = v;
        } else {
            split(v->right, x - get_size(v->left) - 1, v->right, t2);
            t1 = v;
        }
        fix(v);
    }
    void merge(Node*& v, Node* t1, Node* t2) {
        push(t1);
        push(t2);
        if (!t1 || !t2) {
            v = t1 ? t1 : t2;
        } else if (t1->y > t2->y) {
            merge(t1->right, t1->right, t2);
            v = t1;
        } else {
            merge(t2->left, t1, t2->left);
            v = t2;
        }
        fix(v);
    }
};

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // input
    Treap tree;
    int n, m, l, r;
    cin >> n >> m;
    // add source array to treap
    for (int i = 0; i < n; ++i) {
        tree.root = tree.add(tree.root, i, i + 1);
    }
    // process queries
    for (int i = 0; i < m; ++i) {
        cin >> l >> r;
        tree.root = tree.reverse(tree.root, l - 2, r - 2);
    }
    // output
    tree.print(tree.root);
    return 0;
}

