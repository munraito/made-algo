#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h> 
using namespace std;

int split(vector<int>& v, int l, int r) {
    int pivot = v[r];
    int i = l;
    for (int j = l; j <= (r - 1); ++j) {
        //    move all elements <= pivot to the left of it
        if (v[j] <= pivot) {
            iter_swap(v.begin() + i, v.begin() + j);
            ++i;
        }
    }
    //    in the end move pivot to the i
    iter_swap(v.begin() + i, v.begin() + r);
    return i;
}

int split_r(vector<int>& v, int l, int r) {
    //    generate random index and pass it to split() as rightmost element
    srand(time(NULL));
    int x = l + rand() % (r - l + 1);
    iter_swap(v.begin() + x, v.begin() + r);
    return split(v, l, r);
}

int find_k(vector<int> v, int l, int r, int k) {
    //    k should start from l
    k += l;
    //    iterating while we don't find k index
    while (true) {
        //    split, return middle element
        int m = split_r(v, l, r);
        if (m == k) return v[k];
        else if (k < m) r = m - 1;
        else l = m + 1;
    }
}

int main() {
    //    input
    int n;
    cin >> n;
    vector<int> v;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        v.push_back(num);
    }
    //    queries
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << find_k(v, l - 1, r - 1, k - 1) << "\n";
    }
    return 0;
}

