#include <iostream>

using namespace std;

struct Node {
    int key;
    unsigned char height;
    long long sum_st;
    Node* left;
    Node* right;
    Node (int k) {
        key = sum_st = k;
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
    long long sum_range(Node* v, int l, int r) {
        long long sum_l = sum_less_than(v, l);
        long long sum_r = sum_more_than(v, r);
        return get_sum(root) - (sum_l + sum_r);
    }
    Node* insert(Node* v, int x) {
        if (v == nullptr) {
            v = new Node(x);
        } else if (x < v->key) {
            v->left = insert(v->left, x);
        } else if (x > v->key) {
            v->right = insert(v->right, x);
        }
        return balance(v);
    }
private:
    long long sum_less_than(Node* v, int l) {
        if (!v) {
            return 0;
        } else if (v->key > l) {
            // search in left subtree
            return sum_less_than(v->left, l);
        } else if (v->key == l) {
            // get all nodes which are less
            return get_sum(v->left);
        } else {
            // get all nodes which are less and search right
            return get_sum(v->left) + v->key + sum_less_than(v->right, l);
        }
    }
    long long sum_more_than(Node* v, int r) {
        if (!v) {
            return 0;
        } else if (v->key < r) {
            // search in right subtree
            return sum_more_than(v->right, r);
        } else if (v->key == r) {
            // get all nodes which are more
            return get_sum(v->right);
        } else {
            // get all nodes which are more and search left
            return get_sum(v->right) + v->key + sum_more_than(v->left, r);
        }
    }
    long long get_sum(Node* v) {
        return v ? v->sum_st : 0;
    }
    void fix_sum(Node* v) {
        v->sum_st = v->key + get_sum(v->left) + get_sum(v->right);
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
        fix_sum(q);
        fix_sum(p);
        return p;
    }
    Node* rotate_right(Node* p) {
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        fix(p);
        fix(q);
        fix_sum(p);
        fix_sum(q);
        return q;
    }
    Node* balance(Node* v) {
        fix(v);
        fix_sum(v);
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
};

int main() {
    // fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // input
    BST tree;
    int n, val1, val2;
    bool flag = false;
    long long last_sum = 0;
    char oper;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> oper;
        cin >> val1;
        if (oper == '+') {
            if (flag) {
                val1 = (val1 + last_sum) % (int)1e9;
            }
            tree.root = tree.insert(tree.root, val1);
            flag = false;
        } else if (oper == '?') {
            cin >> val2;
            last_sum = tree.sum_range(tree.root, val1, val2);
            flag = true;
            cout << last_sum << "\n";
        }
    }
    return 0;
}

