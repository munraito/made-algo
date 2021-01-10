#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// initial vector capacity
const int MIN_CAP = 2;

class Queue {
public:
	Queue() {
		size = begin = end = 0;
		capacity = MIN_CAP;
		elements = new int[capacity];
	};
	void push(int new_num) {
		if ((end + 1) % capacity == begin) {
			ensure_capacity("push");
		}
		elements[end] = new_num;
		end = (end + 1) % capacity;
	};
	int pop() {
		// calculate actual size
		if (begin > end) {
			//circular case
			size = (capacity - begin) + end;
		} else {
			// regular
			size = end - begin;
		}
		if (size < capacity / 4) {
			ensure_capacity("pop");
		}
		int pop_index = begin;
		begin = (begin + 1) % capacity;
		return elements[pop_index];
	};
	
private:
	int size;
	int capacity;
	int begin;
	int end;
	int* elements;

	void ensure_capacity(string operation) {
		int old_cap = capacity;
		if (operation == "push") {
			capacity *= 2;
		} else {
			capacity /= 2;
		}
		int* temp = new int[capacity];
		if (begin > end) {
			// case for circular, 2 sequential loops
			for (int i = 0; i < end; ++i) {
				temp[i % capacity] = elements[i];
			}
			if (operation == "push") {
				// in case of increasing capacity copy elements to new half
				for (int i = begin; i < capacity; ++i) {
					temp[old_cap + i % capacity] = elements[i];
				}
				begin += old_cap;
			} else {
				// for decreasing copy to beginning
				for (int i = begin; i < old_cap; ++i) {
					temp[i % capacity] = elements[i];
				}
			}
		} else {
			// regular non-circular case
			for (int i = begin; i < end; ++i) {
				temp[i % capacity] = elements[i];
			}
		}
		// track capacity limits
		begin = begin % capacity;
		end = end % capacity;
		delete[] elements;
		elements = temp;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// input
	int n;
	cin >> n;
	Queue q;
	for (int i = 0; i < n; ++i) {
		string operation;
		cin >> operation;
		// process operations
		if (operation == "+") {
			int num;
			cin >> num;
			q.push(num);
		} else if (operation == "-") {
			cout << q.pop() << "\n";
		}
	}
	return 0;
}

