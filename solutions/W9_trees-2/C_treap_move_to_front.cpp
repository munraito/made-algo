#include <iostream>
#include <string>

using namespace std;

struct Node {
    int el;
    int size;
    int y;
    Node* left;
    Node* right;
    Node(int val) {
        el = val;
        size = 1;
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
            print(v->left);
            cout << v->el << " ";
            print(v->right);
        }
    }
    Node* move_to_front(Node* v, int l, int r) {
        Node* t1, * t2, * t21, * t22;
        split(v, l, t1, t2);
        split(t2, r - l, t21, t22);
        merge(v, t21, t1);
        merge(v, v, t22);
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
    int get_size(Node* v) {
        return v ? v->size : 0;
    }
    void fix(Node* v) {
        if (v) {
            v->size = get_size(v->left) + 1 + get_size(v->right);
        }
    }
    void split(Node* v, int x, Node*& t1, Node*& t2) {
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
    for (int i = 1; i < n + 1; ++i) {
        tree.root = tree.add(tree.root, i - 1, i);
    }
    // process queries
    for (int i = 0; i < m; ++i) {
        cin >> l >> r;
        tree.root = tree.move_to_front(tree.root, l - 2, r - 2);
    }
    // output
    tree.print(tree.root);
    return 0;
}

