#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// initial capacity for vector
const int MIN_CAP = 2;

class Stack {
public:
	Stack() {
		size = 0;
		capacity = MIN_CAP;
		elements = new int[capacity];
	};
	void push(int new_num) {
		if (size + 1 > capacity) {
			ensure_capacity("push");
		}
		elements[size] = new_num;
		size++;
	};
	int pop() {
		if (size - 1 < capacity / 4) {
			ensure_capacity("pop");
		}
		size--;
		return elements[size];
	};
	int get_size() {
		return size;
	};

private:
	int size;
	int capacity;
	int* elements;

	void ensure_capacity(string operation) {
		if (operation == "push") {
			capacity *= 2;
		} else {
			capacity /= 2;
		}
		int* temp = new int[capacity];
		for (int i = 0; i < size; ++i) {
			temp[i] = elements[i];
		}
		delete[] elements;
		elements = temp;
	}
};

int main() {
	Stack s;
	// input
	string input;
	getline(cin, input);
	stringstream iss(input);
	string q;
	while (iss >> q) {
		// process operations
		if (q == "+") {
			s.push(s.pop() + s.pop());
		}
		else if (q == "-") {
			int second = s.pop();
			int first = s.pop();
			s.push(first - second);
		}
		else if (q == "*") {
			s.push(s.pop() * s.pop());
		}
		else {
			s.push(stoi(q));
		}
		// detecting end of queries
		if (iss.tellg() == -1) {
			cout << s.pop();
		}
	}
	return 0;
}

