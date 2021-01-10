#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
	// struct to store # of operations and values
	int key;
	int val;
};
class Heap {
public:
	Heap() {
		oper_num = 0;
	}
	void push(int new_val) {
		++oper_num;
		oper_vals.push_back(new_val);
		// push to the end of heap and sift
		heap.push_back({ oper_num, new_val });
		sift_up(heap.size() - 1);
	}
	string pop() { // extract min
		++oper_num;
		oper_vals.push_back(NULL);
		if (heap.size() == 0) {
			return "*";
		}
		// save root to variable, then swap it with the last, remove & sift
		Node root = heap[0];
		iter_swap(heap.begin(), heap.end() - 1);
		heap.erase(heap.end() - 1);
		sift_down();
		return (to_string(root.val) + " " + to_string(root.key));
	}
	void decrease(int pos, int new_val) {
		++oper_num;
		oper_vals.push_back(NULL);
		int old_val = oper_vals[pos - 1];
		oper_vals[pos - 1] = new_val;
		// search for old val in heap
		for (int i = 0; i < heap.size(); ++i) {
			if ((heap[i].val == old_val) && (heap[i].key == pos)) {
				// change for new val & sift
				heap[i].val = new_val;
				sift_up(i);
				break;
			}
		}
	}
private:
	// operations cache
	int oper_num;
	vector<int> oper_vals;
	// main vector
	vector<Node> heap;

	void sift_up(int i) {
		//sift up from child to root, fixing positions
		while ((i > 0) && (heap[i].val < heap[(i - 1) / 2].val)) {
			iter_swap(heap.begin() + i, heap.begin() + (i - 1) / 2);
			i = (i - 1) / 2;
		}
	}
	void sift_down() {
		// sift all the way down to fix positions
		int i = 0;
		while (2 * i + 1 < heap.size()) {
			int cur = heap[i].val;
			int left = heap[2 * i + 1].val;
			int right;
			// checking case when only left child is present
			if ((2 * i + 2) == heap.size()) {
				right = 1e9 + 1; // max possible val + 1
			} else {
				right = heap[2 * i + 2].val;
			}
			// swap children with the parent
			if ((left <= right) && (left <= cur)) {
				// when left child is the minimum
				iter_swap(heap.begin() + i, heap.begin() + 2 * i + 1);
				i = 2 * i + 1;
			} else if ((right <= left) && (right <= cur)) {
				// or right child is the minimum
				iter_swap(heap.begin() + i, heap.begin() + 2 * i + 2);
				i = 2 * i + 2;
			} else {
				break;
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	Heap h;
	// input
	string line;
	while (getline(cin, line)) {
		istringstream iss(line);
		vector<string> v;
		for (string s; iss >> s; ) {
			v.push_back(s);
		}
		if (v[0] == "push") {
			h.push(stoi(v[1]));
		} else if (v[0] == "decrease-key") {
			h.decrease(stoi(v[1]), stoi(v[2]));
		} else if (v[0] == "extract-min") {
			cout << h.pop() << "\n";
		}
	}
	return 0;
}

