//LinkedList.h
#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H
#define LINKEDLIST_EMPTY 0
#define LINKEDLIST_NOTFOUND 1

#include <iostream>
using namespace std;


template <class T>
class LinkedListExp{
public:
	LinkedListExp(int);
	LinkedListExp(const LinkedListExp&);
	~LinkedListExp();
	void DisplayMsg() const;
private:
	const int id_msg;
	static string msg[];
};

template <class T>
string LinkedListExp<T>::msg[] = {"Linked List is Empty.", "The element you are looking for is not available."};

template <class T>
LinkedListExp<T>::LinkedListExp(int n) : id_msg(n) { }

template <class T>
LinkedListExp<T>::LinkedListExp(const LinkedListExp& l) : id_msg(l.id_msg) { }

template <class T>
LinkedListExp<T>::~LinkedListExp() { }

template <class T>
void LinkedListExp<T>::DisplayMsg() const {
	cerr << msg[id_msg] << endl;
}

template <class T>
struct node {
	T data;
	node<T>* next;
};


template <class T>
class LinkedList{
private:
	node<T>* first;

public:
	LinkedList();
	LinkedList(T);
	LinkedList(const LinkedList&);
	~LinkedList();

	bool isEmpty() { return first == NULL; }
	void addFirst(T);
	void addLast(T);
	void addAtIdx(int, T);
	T delFirst();
	T delLast();
	T delAtIdx(int);
	//void sort();
	void print();
};

template <class T>
LinkedList<T>::LinkedList(){
	first = NULL;
}

template <class T>
LinkedList<T>::LinkedList(T val){
	first = new node<T>;
	first->data = val;
	first->next = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList& L){
	first = new node<T>;
	first->data = L.first->data;
	node<T>* n1 = first;
	node<T>* n2 = L.first->next;
	while (n2 != NULL){
		n1->next = new node<T>;
		n1 = n1->next;
		n1->data = n2->data;
		n2 = n2->next;
	}
	n1->next = NULL;
}

template <class T>
LinkedList<T>::~LinkedList(){
	delete first;
}

template <class T>
void LinkedList<T>::addFirst(T val){
	node<T>* newElmt = new node<T>;
	newElmt->data = val;
	newElmt->next = first;
	first = newElmt;
}

template <class T>
void LinkedList<T>::addLast(T val){
	if (isEmpty()){
		addFirst(val);
	} else {
		node<T>* curr = first;
		while(curr->next != NULL){
			curr = curr->next;
		}
		// curr is the last element now
		node<T>* newElmt = new node<T>;
		newElmt->data = val;
		curr->next = newElmt;
		newElmt->next = NULL;
	}
}

template <class T>
void LinkedList<T>::addAtIdx(int idx, T val){
	if (idx == 0){
		addFirst(val);
	} else {
		bool found = false;
		node<T>* curr = first;
		int i = 0;
		while (curr != NULL && !found ){
			if (i != idx-1){
				curr = curr->next;
				i++;
			} else {
				found = true;
			}
		}
		if (curr == NULL) throw (LinkedListExp<T>(LINKEDLIST_NOTFOUND));
		else {
			node<T>* newNode = new node<T>;
			newNode->data = val;
			newNode->next = curr->next;
			curr->next = newNode;
		}
	}
}

template <class T>
T LinkedList<T>::delFirst(){
	if (isEmpty()) throw(LinkedListExp<T>(LINKEDLIST_EMPTY));
	else{
		T ret_val;
		ret_val = first->data;
		first = first->next;
		delete first;
		return ret_val;
	}
}

template <class T>
T LinkedList<T>::delLast(){
	if (isEmpty()) throw(LinkedListExp<T>(LINKEDLIST_EMPTY));
	else{
		node<T>* prev = NULL;
		node<T>* curr = first;
		while(curr->next != NULL){
			prev = curr;
			curr = curr->next;
		}
		if ( prev == NULL ){
			delFirst();
		} else {
			T ret_val = curr->data;
			prev->next = NULL;
			delete curr;
			return ret_val;	
		}
	}
}

template <class T>
T LinkedList<T>::delAtIdx(int idx){
	if (isEmpty()) throw(LinkedListExp<T>(LINKEDLIST_EMPTY));
	else if (idx == 0){
		delFirst();
	} else {
		int i = 0;
		node<T>* prev = NULL;
		node<T>* curr = first;
		while(curr->next != NULL && i < idx){
			prev = curr;
			curr = curr->next;
			i++;
		}
		T ret_val = curr->data;
		prev->next = curr->next;
		delete curr;
		return ret_val;
	}
}

template <class T>
void LinkedList<T>::print(){
	node<T>* curr = first;
	cout << "[";
	while (curr != NULL){
		cout << curr->data;
		curr = curr->next;
		if (curr != NULL){
			cout << ",";
		}
	}
	cout << "]";
}

#endif