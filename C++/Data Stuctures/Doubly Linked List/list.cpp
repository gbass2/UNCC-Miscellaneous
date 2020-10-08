#include "list.h"

using namespace std;

// Node class implemenation

template <typename T>
Node<T>::Node(T element) { // Constructor
	data = element;
	previous = nullptr;
	next = nullptr;
}

// List implementation

template <typename T>
List<T>::List() {
	head = nullptr;
	tail = nullptr;
}

template <typename T>
List<T>::List(const List& rhs) // Copy constructor - homework
{
	// Checking to see if rhs is empty
	if(rhs.head == nullptr){
		this->head = this->tail = nullptr;
	} else { // We do a deep copy
		this->tail = nullptr;
		Node<T>* current = rhs.head;

		while(current->next != nullptr){
			push_back(current->data);
			current = current->next;
		}
		push_back(current->data);
	}
}

template <typename T>
List<T>::~List() { // Destructor
	for(Node<T>* n = head; n != nullptr; n = n->next) {
		delete n;
	}

}

template <typename T>
void List<T>::push_back(T element) {
	Node<T>* new_node = new Node<T>(element);
	if (tail == nullptr) { // Empty list
		head = new_node;
		tail = new_node;
	} else {
		new_node->previous = tail;
		tail->next = new_node;
		tail = new_node;
   }
}

template <typename T>
void List<T>::insert(Iterator<T> iter, T element) {
	if (iter.position == nullptr) {
		push_back(element);
		return;
	}

	Node<T>* after = iter.position;
	Node<T>* before = after->previous;
	Node<T>* new_node = new Node<T>(element);
	new_node->previous = before;
	new_node->next = after;
	after->previous = new_node;
	if (before == nullptr) {
		head = new_node;
	} else {
		before->next = new_node;
	}
}

template <typename T>
Iterator<T>  List<T>::erase(Iterator<T> iter) {
	Node<T>* remove = iter.position;
	Node<T>* before = remove->previous;
	Node<T>* after = remove->next;
	if (remove == head) {
		head = after;
	} else {
		before->next = after;
	}
	if (remove == tail) {
		tail = before;
	} else {
		after->previous = before;
	}
	delete remove;
	Iterator<T> r;
	r.position = after;
	r.container = this;
	return r;
}


template <typename T>
Iterator<T> List<T>::begin() {
	Iterator<T> iter;
	iter.position = head;
	iter.container = this;
	return iter;
}

template <typename T>
Iterator<T> List<T>::end() {
	Iterator<T> iter;
	iter.position = nullptr;
	iter.container = this;
	return iter;
}

// Iterator implementation

template <typename T>
Iterator<T>::Iterator() {
	position = nullptr;
	container = nullptr;
}


template <typename T>
T Iterator<T>::get() const {
	return position->data;
}

template <typename T>
void Iterator<T>::next() {
	position = position->next;
}

template <typename T>
void Iterator<T>::previous() {
	if (position == nullptr) {
		position = container->tail;
	} else {
		position = position->previous;
	}
}

template <typename T>
bool Iterator<T>::equals(Iterator<T> other) const {
   return position == other.position;
}
