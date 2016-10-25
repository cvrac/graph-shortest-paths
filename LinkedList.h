#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include <assert.h>

template <class T>
class LinkedList {
	private:
		struct node {
			T data;
			node *next;
			node(const T& data, node *n);
		};
		node *head;
		node *back;
		node *current;
		unsigned int _size;
	public:
		LinkedList();
		~LinkedList();
		int size();
		bool empty();
		T *push_front(const T& data);
		bool pop_front();
		T pop();
		bool push_back(const T& data);
		bool insert(const T& data);
		bool rem(const T& data);
		T *member(const T& data);
		bool exists(const T& data);
		T *get_next();
		int position(const T& data);
		void print();
		void curr_head();
		bool check_next();
		template <class G>
		friend std::ostream& operator<<(std::ostream& out, const LinkedList<G>& l);
		template <class G>
		friend std::ostream& operator<<(std::ostream& out, const LinkedList<G>* l);		
};

template <class T>
LinkedList<T>::node::node(const T& d, node *n) : data(d), next(n) {}

template <class T>
LinkedList<T>::LinkedList() : head(NULL), back(NULL), current(NULL), _size(0) {}

template <class T>
LinkedList<T>::~LinkedList() {
	if (_size > 0) {
		current = head;
		node *tempx ;
		while (current != NULL) {
			tempx = current;
			current = current->next;
			delete tempx;
		}
		current = NULL;
		head = NULL;
	}
}

template <class T>
int LinkedList<T>::size() {
	return _size;
}

template <class T>
bool LinkedList<T>::empty() {
	return (this->head == NULL);
}

template <class T>
T *LinkedList<T>::push_front(const T& data) {

	node *temp = new node(data, head);
	assert(temp != NULL);

	if (head == NULL)
		back = temp;
	head = temp;
	current = head;
	_size++;
	return &temp->data;
}

template <class T>
bool LinkedList<T>::push_back(const T& data) {
	node *temp = new node(data, NULL);
	assert(temp != NULL);

	if (temp == NULL)
		return false;
	
	// node *prev = NULL;
	// current = head;

	// while (current != NULL) {
	// 	prev = current;
	// 	current = current->next;
	// }

	// if (prev == NULL) 
	// 	head = temp;
	// else 
	// 	prev->next = temp;

	if (head == NULL) {
		head = temp;
		back = temp;
	} else {
		node *prev = back;
		prev->next = temp;
		back = temp;
	}

	current = head;
	_size++;

	return true;
}

template <class T>
bool LinkedList<T>::insert(const T& data) {
	node *temp = new node(data, NULL);
	assert(temp != NULL);
	bool found_pos = false;

	if (temp == NULL)
		return false;
	
	//Empty list case

	if (head == NULL) {
		head = temp;
		current = head;
		_size++;
		return true;
	}

	node *prev = NULL;
	current = head;

	while (current != NULL) {
		if (temp->data <= current->data)
			break;
		prev = current;
		current = current->next;
	}

	//Insertion at the front of the list
	if (prev == NULL) {
		temp->next = head;
		head = temp;
	} else {
		temp->next = prev->next;
		prev->next = temp;
	}

	current = head;
	_size++;

	return true;
}

template <class T>
bool LinkedList<T>::pop_front() {
	if (this->empty() == true) return false;
	node *temp = head;
	head = head->next;
	current = head;
	_size--;
	delete temp;
	return true;
}

template <class T>
T LinkedList<T>::pop() {
	T returnt;
	node *temp = head;
	head = head->next;
	current = head;
	_size--;
	returnt = temp->data;
	delete temp;
	return returnt;
}

template <class T>
bool LinkedList<T>::rem(const T& data) {
	node *temp = head;
	node *prev = NULL;

	if (data == temp->data) {
		head = temp->next;
		current = head;
		delete temp;
		_size--;
		temp = NULL;
		return true;
	}

	temp = temp->next;
	prev = head;

	while (temp != NULL) {
		if (temp->data == data) {
			prev->next = temp->next;
			current = head;
			delete temp;
			temp = NULL;
			_size--;
			return true;
		} 
		prev = temp;
		temp = temp->next;
	}

	current = head;
	return false;

}

template <class T>
void LinkedList<T>::print() {
	current = head;
	while (current != NULL) {
		std::cout << current->data;
		current = current->next;
	}
	current = head;
}

template <class T>
T *LinkedList<T>::member(const T& d) {
	node *temp = head;
	while (temp != NULL) {
		if (d == temp->data) return &temp->data;
		temp = temp->next;
	}
	return NULL;
}

template <class T>
bool LinkedList<T>::exists(const T& d) {
	node *temp = head;
	while (temp != NULL) {
		if (d == temp->data) return true;
		temp = temp->next;
	}
	return false;
}

template <class T>
T *LinkedList<T>::get_next() {
	node *temp;
	if (current != NULL) {
		temp = current;
		current = current->next;
		return &temp->data;
	} else {
		current = head;
		return NULL;
	}
}

template <class T>
void LinkedList<T>::curr_head() {
	current = head;
}

template <class T>
bool LinkedList<T>::check_next() {
	if (current != NULL) {
		if (current->next == NULL)
			return false;
		else 
			return true;
	}
	return false;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T>& l) {
    typename LinkedList<T>::node *temp = l.head;
    while (temp != NULL) {
        out << temp->data << std::endl;
        temp = temp->next;
    }

    return out;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T>* l) {
	if (l == NULL) return out;
	if (l->empty() == true) return out;

    typename LinkedList<T>::node *temp = l->head;
    while (temp != NULL) {
        out << temp->data << std::endl;
        temp = temp->next;
    }

    return out;
}

#endif