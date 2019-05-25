#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T> class MyList;

template <class T>
class NodeList{
public:
    NodeList<T>(T number, NodeList<T>*next = nullptr){ 
        this->number = number; 
        this->next = next;
    }
    ~NodeList<T>(){};
    T number;
    NodeList<T> *next;
    friend class MyList<T>;
};

template <class T>
class MyList {
public:
    NodeList<T> *first;
    NodeList<T> *last;
    size_t size;
    MyList();
    void addfirst(T newElem);
    void clear();
    void push_back(T LastElem);
    void push_front(T FirstElem);
    void pop_back();
    void pop_front();
    bool isEmpty();
    void insert (int index, T newElem);
    T at(int index);
    void set(int index, T newElem);
    void remove(int index);
    size_t get_size() const;
};

template <class T>
MyList<T>::MyList() {
    this->first = nullptr;
    this->last = nullptr;
    size=0;
}

template <class T>
void MyList<T>::addfirst(T newElem){
    NodeList<T> *newNode = new NodeList<T> (newElem);
    this->first = newNode;
    this->last = newNode;
    this->last->next = nullptr;
    this->size = 1;
}

template <class T>
void MyList<T>::clear(){
    NodeList<T> *newNode = first;
	while (newNode != nullptr) {
		NodeList<T>* next = newNode->next;
		delete newNode;
		newNode = next;
	}
	first = last = nullptr;
	size = 0;
}

template <class T>
size_t MyList<T>::get_size() const {
    return size;
}

template <class T>
void MyList<T>::push_back(T LastElem){
    NodeList<T> *newNode;
    newNode = new NodeList<T>(LastElem);
    if (this->size == 0){
        addfirst(LastElem);
    }
    else {
        last->next= newNode;
        last = last->next;
        this->size++;
    }
}

template <class T>
void MyList<T>::push_front(T FirstElem){
    NodeList<T> *newNode;
    newNode = new NodeList<T>(FirstElem);
    newNode->next = this->first;
    this->first = newNode;
    this->size++;
}

template <class T>
void MyList<T>::pop_back(){
    if (size == 0){     //if the list is empty
		throw out_of_range("List is empty");
    }
    if (size==1){     //if there is only one element in list
        first = nullptr;
        last = nullptr;
		delete last;
		delete first;
    }
	else{
        NodeList<T> *newNode;
        newNode = first;
		while (newNode->next != last) {
			newNode = newNode->next;
		}
		newNode->next = nullptr;
		delete last;
		last = newNode;
    }
	size--;
}

template <class T>
void MyList<T>::pop_front(){
    if (size == 0){     //if the list is empty
		throw out_of_range("List is empty");
    }
    if (size == 1){     //if there is only one element in list
        first = nullptr;
        last = nullptr;
		delete first;
		delete last;
    }
    else{
        NodeList<T> *newNode;
        newNode = first->next;
		first->next = nullptr;
        delete first;
        first = newNode;
    }
	size--;
}

template <class T>
bool MyList<T>::isEmpty(){
    if (size == 0){
        return true;
    } else {
        return false;
    }
}

template <class T>
void MyList<T>::insert(int index, T newElem){  ///algorithm be like "index 4, we found 3, new will be 4, new->next is 5"
	if (index >= size || index < 0) {
		throw out_of_range("Invalid Index");
	}
	else {
		int cnt = 0;
		NodeList<T>* current = first;
		if (index == 0) {
			push_front(newElem);
		}
		else {
			while (cnt != index - 1) {
				current = current->next;
				cnt++;
			}
			NodeList<T>* old = new NodeList<T>(newElem, current->next);
			current->next = old;
		}
		size++;
	}
}

template <class T>
T MyList<T>::at(int index){  
    auto newNode = first;
	if (index >= size || index<0) {
		throw out_of_range("Element doesn't exist");
	}
	else {
		int cnt = 0;
		NodeList<T>* current;
		current = first;
		while (cnt != index) {
			current = current->next;
			cnt++;
		}
		return current->number;
    }
}

template <class T>
void MyList<T>::set(int index, T newElem){
    if(index>=size || index<0) {
		throw out_of_range ("There's no this index");
    }
	else {
		NodeList<T>* oldNode = this->first;
		for (int i = 0; i < index; i++) {
			oldNode = oldNode->next;
		}
		oldNode->number = newElem;
	}
}

template <class T>
ostream& operator<< (ostream &out, const MyList<T> &myList){
    NodeList<T> *newNode;
    newNode = myList.first;
    for (int i = 0; i<myList.size; i++){
        out << "Index: " << i << "; Element: " << newNode->number << endl;
        newNode = newNode->next;
    }
    return out;
}


template <class T>
void MyList<T>::remove(int index){
	if (index >= size || index < 0) {
		throw out_of_range("Invalid Index");
	}
	else {
		NodeList<T>* deletingNode = first;
		NodeList<T>* prev = nullptr;
		for (int i = 0; i < index; i++) {
			prev = deletingNode;
			deletingNode = deletingNode->next;
		}
		if (deletingNode == first) { // prev == nullptr
			first = first->next;
		}
		else
			if (deletingNode == last) {
				prev->next = nullptr;
				last = prev;
			}
			else {
				prev->next = deletingNode->next;
			}
		delete deletingNode;
		size--;
	}
}