// Doubly linked list
#ifndef LIST_H
#define LIST_H

template<typename T> class List;
template<typename T> class Iterator;

template <typename T>
class Node {
	public:
		Node(T element);
	private:
		T data; 
		Node* previous;
		Node* next;
	friend class List<T>;
	friend class Iterator<T>;
};

template <typename T>
class List {
	public:
		List(); // Constructor
		List(const List& rhs); // Copy constructor - Homework 
		~List(); // Destructor
		void push_back(T element); // Inserts to back of list
		void insert(Iterator<T> iter, T element); // Insert after location pointed by iter 
		Iterator<T> erase(Iterator<T> iter);  // Delete from location pointed by iter
		Iterator<T> begin(); // Point to beginning of list
		Iterator<T> end(); // Point to past end of list
	private:
		Node<T>* head;
		Node<T>* tail;
	friend class Iterator<T>;
};


template <typename T>
class Iterator {
	public:
		Iterator();
		T get() const; // Get value pointed to by iterator
		void next(); // Advance iterator forward
		void previous(); // Advance iterator backward
		bool equals(Iterator<T> other) const; // Compare values pointed to by two iterators
	private:
		Node<T>* position; // Node pointed to by iterator
		List<T>* container; // List the iterator is used to iterattoe
	friend class List<T>;
};

#endif
