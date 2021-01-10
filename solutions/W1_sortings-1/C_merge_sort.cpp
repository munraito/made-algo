#include <iostream>
#include <vector>
using namespace std;

vector<int> merge(const vector<int>& left, const vector<int>& right) {
    int l_size = left.size(), r_size = right.size(), i = 0, j = 0;
    vector<int> res;
    while ((i + j) < (l_size + r_size)) {  // iterating till the end of arrays
        if ((j == r_size) || ((i < l_size) && (left[i] < right[j]))) {  
            // case for left side
            res.push_back(left[i]);
            ++i;
        } else {  // case for right side
            res.push_back(right[j]);
            ++j;
        }
    }
    return res;
}

vector<int> merge_sort(const vector<int>& arr) {
    int arr_size = arr.size();
    if (arr_size < 2) return arr;  // base case

    vector<int> left, right;  // split to 2 halves
    for (int i = 0; i < (arr_size / 2); ++i) left.push_back(arr[i]);
    for (int i = (arr_size / 2); i < arr_size; ++i) right.push_back(arr[i]);

    left = merge_sort(left);  // recursively merge halves
    right = merge_sort(right);
    return merge(left, right);
}
int main() {
    // input
    int N;
    cin >> N;
    vector <int> nums;
    for (int i = 0; i < N; ++i) {
        int num;
        cin >> num;
        nums.push_back(num);
    }
    // sort
    nums = merge_sort(nums);
    // output
    for (int num : nums) cout << num << " ";
    return 0;
}

