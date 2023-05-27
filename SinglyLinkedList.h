#include <iostream>
using namespace std;


struct SinglyNode {

	int x;
	int y;
	int counterSize;
	SinglyNode* next;


};


struct SinglyLinkedList {

	SinglyNode* head;

	SinglyLinkedList();
	~SinglyLinkedList();

	bool empty() const;
	void addFront(const int x, const int y,const int counterSize);
	void removeFront();
	void removeBack();
	void print();
	//void insertOrdered(const int& x, const int& y, const int& counterSize);
};

bool SinglyLinkedList::empty() const {

	return head == NULL;

}

SinglyLinkedList::SinglyLinkedList() {

	head = NULL;
}

SinglyLinkedList::~SinglyLinkedList() {

	while (!empty()) removeFront();
}

void SinglyLinkedList::addFront(const int x, const int y,const int counterSize) {

	SinglyNode* coordinatePoint = new SinglyNode;
	coordinatePoint->x = x;
	coordinatePoint->y = y;
	coordinatePoint->counterSize = counterSize;
	coordinatePoint->next = head;
	head = coordinatePoint;

}

void SinglyLinkedList::removeFront() {

	if (empty()) {
		cout << "list is empty!" << endl;
	}

	SinglyNode* temp = head;

	head = head->next;
	delete temp;
}

void SinglyLinkedList::removeBack() {

	if (empty()) {
		cout << "list is empty!" << endl;
	}

	SinglyNode* previous = head;

	if (previous->next == NULL) {

		delete head;
		delete previous;
	}
	else {

		while (previous->next->next != NULL) {
			previous = previous->next;
		}
		delete previous->next;

		previous->next = NULL;
	}
}


void SinglyLinkedList::print() {

	if(empty()){
	
		cout << "list is empty"<<endl;
	}

	SinglyNode* current = head;

	while (current->next != NULL) {
		cout << current->x << "    " << current->y << endl;
		current = current->next;
	}


}