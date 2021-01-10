#include <iostream>
#include <vector>
using namespace std;

long long merge(vector<int>& arr, const vector<int>& left, const vector<int>& right) {
    // counts number of inversions, sorts array in-place
    int l_size = left.size(), r_size = right.size(), i = 0, j = 0;
    long long counter = 0;
    while (i + j < l_size + r_size) { 
        if ((j == r_size) || ((i < l_size) && (left[i] < right[j]))) {
            arr[i + j] = left[i];
            ++i;
        } else {  // case where inversion is found
            arr[i + j] = right[j];
            ++j;
            // inversions are all elements in the left array,
            // which stand to the right of i
            counter += l_size - i;
        }
    }
    return counter;
}

long long count_inversions(vector<int>& arr) {
    int arr_size = arr.size();
    if (arr_size < 2) return 0;

    vector<int> left, right;
    for (int i = 0; i < (arr_size / 2); ++i) left.push_back(arr[i]);
    for (int i = (arr_size / 2); i < arr_size; ++i) right.push_back(arr[i]);

    return count_inversions(left) + count_inversions(right) + merge(arr, left, right);
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
    // count
    long long inversions = count_inversions(nums);
    // output
    cout << inversions;
    return 0;
}

