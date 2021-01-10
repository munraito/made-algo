#include <iostream>

using namespace std;

struct Node {
    int key;
    unsigned char height;
    int size;
    Node* left;
    Node* right;
    Node (int k) {
        key = k;
        left = right = nullptr;
        height = size = 1;
    }
};

class BST {
public:
    Node* root;
    BST() {
        // init empty tree
        root = nullptr;
    }
    int k_max(Node* v, int k) {
        int r_size = get_size(v->right);
        if (r_size == k - 1) {
            // in this subtree there are k - 1 elements higher that the root
            return v->key;
        } else if (r_size >= k) {
            // maximum is in the lower right subtree
            return k_max(v->right, k);
        } else {
            return k_max(v->left, k - r_size - 1);
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
private:
    int get_size(Node* v) {
        return v ? v->size : 0;
    }
    void fix_size(Node* v) {
        v->size = get_size(v->left) + 1 + get_size(v->right);
    }
    unsigned char get_height(Node* v) {
        return v ? v->height : 0;
    }
    int get_balance_ratio(Node* v) {
        return get_height(v->right) - get_height(v->left);
    }
    void fix(Node* v) {
        unsigned char h_l = get_height(v->left);
        unsigned char h_r = get_height(v->right);
        v->height = (h_l > h_r ? h_l : h_r) + 1;
    }
    Node* rotate_left(Node* q) {
        Node* p = q->right;
        q->right = p->left;
        p->left = q;
        fix(p);
        fix(q);
        fix_size(q);
        fix_size(p);
        return p;
    }
    Node* rotate_right(Node* p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        fix(p);
        fix(q);
        fix_size(p);
        fix_size(q);
        return q;
    }
    Node* balance(Node* v) {
        fix(v);
        fix_size(v);
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
};

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // input
    BST tree;
    int n, oper, val;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> oper;
        cin >> val;
        if (oper == 1) {
            tree.root = tree.insert(tree.root, val);
        } else if (oper == -1) {
            tree.root = tree.remove(tree.root, val);
        } else {
            cout << tree.k_max(tree.root, val) << "\n";
        }
    }
    return 0;
}

