#include <iostream>
#include <vector>
using namespace std;

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
    // insertion sort
    for (int i = 1; i < N; ++i) {
        int j = i;
        while ((j > 0) && (nums[j - 1] > nums[j])) {
            // swap
            int temp = nums[j - 1];
            nums[j - 1] = nums[j];
            nums[j] = temp;
            --j;
        }
    }
    // output
    for (int num : nums) {
        cout << num << " ";
    }
    return 0;
}

