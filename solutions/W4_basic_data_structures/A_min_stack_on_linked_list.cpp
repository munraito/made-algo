#include <iostream>

using namespace std;

class Stack {
public:
	Stack() {
		// initialize empty stacks of values and minimums
		head = NULL;
		min_head = NULL;
	}
	void push(int new_num) {
		// input data and pointer to previous head of stack
		Node* temp = new Node;
		temp->data = new_num;
		temp->next = head;
		// also push to min stack if it is empty
		if (min_head == NULL) {
			push_min(new_num);
		}
		// or if new_num is less than previous minimum
		else if (temp->data <= min_head->data) {
			push_min(new_num);
		}
		// move head to point at the new node
		head = temp;
	}
	void pop() {
		// move the head pointer to the next node
		Node* temp = head;
		head = head->next;
		// also remove from min stack if they match
		if (temp->data == min_head->data) {
			pop_min();
		}
		delete temp;
	}
	int find_min() {
		return min_head->data;
	}
private:
	struct Node {
		int data;
		Node* next;
	};
	Node* head;
	Node* min_head;
	void push_min(int new_min) {
		Node* temp = new Node;
		temp->data = new_min;
		temp->next = min_head;
		min_head = temp;
	}
	void pop_min() {
		Node* temp = min_head;
		min_head = min_head->next;
		delete temp;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	// input
	int n;
	cin >> n;
	Stack s;
	// queries
	for (int i = 0; i < n; ++i) {
		int operation;
		cin >> operation;
		if (operation == 1) {
			int new_num;
			cin >> new_num;
			s.push(new_num);
		}
		else if (operation == 2) {
			s.pop();
		}
		else if (operation == 3) {
			cout << s.find_min() << "\n";
		}
	}

	return 0;
}

