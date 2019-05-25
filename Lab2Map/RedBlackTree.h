#include <iostream>
#include "mylist.h"
using namespace std;

template <class T, class V> class Map;
template <class T, class V> class Node;

/** 3 types of exceptions:
1) Left son true parent true Uncle:
Just repaint the nodes
2) Right son true parent false Uncle:
repaint nodes then rotate Left
3) Left son true parent false Uncle:
repaint nodes then rotate Right
*/
template <class T, class V>
class Map{ 
private:
	void LeftRotate(Node<T,V>* x);
	void RightRotate(Node<T,V>* x);
	void insertFix(Node<T,V>* newNode); 
	void FixDelete(Node<T,V>* current, Node<T,V>* fixParent); 
public:
    Node<T,V> *root;
    Map();
	~Map();
    void insert(T key, V value);
    Node<T,V> *FindNode(T key);
	Node<T, V>* FindValue(V value);
    void remove(T key);
    void Clear();
	MyList<T>* get_keys();
	void get_keys_node(MyList<T> *keyList, Node<T,V> *root);
	MyList<V>* get_values();
	void get_keys_value(MyList<V>* valueList, Node<T, V>* root);
	Node<T, V>* getRoot();

	MyList<V>* get_colors();//recursive in-order travel for unit-tests
	void get_colors_node(MyList<V>* valueList, Node<T, V>* root);
};

template <class T, class V>
Node <T, V>* Map<T, V>::getRoot() {
	return root;
}

template <class T, class V>
MyList<T> *Map<T,V>::get_keys() {
	MyList<T>* keyList = new MyList<T>();
	Node<T, V>* starting_point = root;
	get_keys_node(keyList, starting_point);
	if (keyList->size != 0) {
		return keyList;
	}
	else throw out_of_range("List is empty");
}


template <class T, class V>
void Map<T, V>::get_keys_node(MyList<T> *keyList, Node<T,V> *root) {
	if (root != nullptr) {
		get_keys_node(keyList, root->left);
		keyList->push_back(root->key);
		get_keys_node(keyList, root->right);
	}
}

template <class T, class V>
MyList<V>* Map<T, V>::get_values() {
	MyList<V>* valueList = new MyList<V>();
	Node<T, V>* starting_point = root;
	get_keys_value(valueList, starting_point);
	if (valueList->size != 0) {
		return valueList;
	}
	else throw out_of_range("List is empty");
}


template <class T, class V>
void Map<T, V>::get_keys_value(MyList<V>* valueList, Node<T, V>* root) {
	if (root != nullptr) {
		get_keys_value(valueList, root->left);
		valueList->push_back(root->value);
		get_keys_value(valueList, root->right);
	}
}

template <class T, class V>
MyList<V>* Map<T, V>::get_colors() {
	MyList<V>* valueList = new MyList<V>();
	Node<T, V>* starting_point = root;
	get_colors_node(valueList, starting_point);
	return valueList;
}


template <class T, class V>
void Map<T, V>::get_colors_node(MyList<V>* valueList, Node<T, V>* root) {
	if (root != nullptr) {
		get_colors_node(valueList, root->left);
		valueList->push_back(root->color);
		get_colors_node(valueList, root->right);
	}
}

template <class T, class V>
class Node {
private:
	bool getColor();
	void clearNode();
	bool color;   //false/0 = BLACK; true/1 = RED
public:
	Node* right;
	Node* left;
	Node* parent;
	V value;
	T key;
	Node();
	Node(T key, V value, Node* parent);
	~Node();
	friend class Map<T, V>;
};


template <class T, class V>
Node<T, V>::Node() {
	this->right = nullptr;
	this->left = nullptr;
	this->parent = nullptr;
	this->color = false;
}

template <class T, class V>
Node<T, V>::Node(T key, V value, Node<T, V>* parent) {
	this->right = nullptr;
	this->left = nullptr;
	this->parent = parent;
	this->key = key;
	this->value = value;
	this->color = true;
}

template <class T, class V>
Node<T, V>::~Node() {
	this->right = nullptr;
	this->left = nullptr;
	this->parent = nullptr;
	this->color = false;
}

template <class T, class V>
void Node<T, V>::clearNode() {
	if (this != nullptr) {
		left->clearNode();
		right->clearNode();
		delete this;
	}
}

template <class T, class V>
bool Node<T, V>::getColor() {
	if (this != nullptr) {
		return this->color;
	}
	else
		return false;
}

template <class T, class V>
Map<T, V>::Map() {
	this->root = nullptr;
	root = nullptr;
	//falseHeight = 0;
}

template <class T, class V>
Map<T,V>::~Map() {
	Clear();
}

template <class T, class V>
void Map<T, V>::LeftRotate(Node<T, V>* fixingNode) {
	Node<T, V>* rightSon = fixingNode->right;
	fixingNode->right = rightSon->left;
	if (rightSon->left != nullptr) {
		rightSon->left->parent = fixingNode;
	}
	if (rightSon != nullptr) {
		rightSon->parent = fixingNode->parent;
	}
	if (fixingNode->parent != nullptr) {
		if (fixingNode == fixingNode->parent->left) {
			fixingNode->parent->left = rightSon;
		}
		else {
			fixingNode->parent->right = rightSon;
		}
	}
	else {
		root = rightSon;
	}
	rightSon->left = fixingNode;
	if (fixingNode != nullptr) {
		fixingNode->parent = rightSon;
	}
}

template <class T, class V>
void Map<T, V>::RightRotate(Node<T, V> * fixingNode) {
	Node<T, V>* leftSon = fixingNode->left;
	fixingNode->left = leftSon->right;
	if (leftSon->right != nullptr) {
		leftSon->right->parent = fixingNode;
	}
	if (leftSon != nullptr) {
		leftSon->parent = fixingNode->parent;
	}
	if (fixingNode->parent != nullptr) {
		if (fixingNode == fixingNode->parent->right) {
			fixingNode->parent->right = leftSon;
		}
		else
			fixingNode->parent->left = leftSon;
	}
	else {
		root = leftSon;
	}
	leftSon->right = fixingNode;
	if (fixingNode != nullptr) {
		fixingNode->parent = leftSon;
	}
}

template <class T, class V>
void Map<T, V>::insertFix(Node<T, V> * newNode) {
	Node<T, V>* uncle;
	while (newNode != root && newNode->parent->color == true) {
		if (newNode->parent == newNode->parent->parent->left) { ///left subtree
			if (newNode->parent->parent->right == nullptr) ///if grandfather doesn't exist
				uncle = new Node<T, V>();
			else
				uncle = newNode->parent->parent->right; ///uncle is right son of grandfather
			if (uncle->color == true) {
				newNode->parent->color = false;
				uncle->color = false;
				newNode->parent->parent->color = true;
				newNode = newNode->parent->parent;
			}
			else {
				if (newNode == newNode->parent->right) {
					newNode = newNode->parent;
					LeftRotate(newNode); ///if uncle color is false and node is right son
				}

				newNode->parent->color = false;
				newNode->parent->parent->color = true;
				RightRotate(newNode->parent->parent); ///when parent is false and grandfather is true
			}
		}
		else {
			if (newNode->parent->parent->left == nullptr)
				uncle = new Node<T, V>();
			else
				uncle = newNode->parent->parent->left;
			if (uncle->color == true) {
				newNode->parent->color = false;
				uncle->color = false;
				newNode->parent->parent->color = true;
				newNode = newNode->parent->parent;
			}
			else {
				if (newNode == newNode->parent->left) {
					newNode = newNode->parent;
					RightRotate(newNode);
				}
				newNode->parent->color = false;
				newNode->parent->parent->color = true;
				LeftRotate(newNode->parent->parent);
			}
		}
	}
	root->color = false;
}

template <class T, class V>
void Map<T, V>::insert(T key, V value) {
	Node<T, V>* current, * parent, * newNode;
	current = root;
	parent = nullptr;
	while (current != nullptr) {   ///find where to insert
		parent = current;
		if (key < current->key) {
			current = current->left;
		}
		else
			current = current->right;
		}
	newNode = new Node<T, V>(key, value, parent); ///set up new Node

	if (parent != nullptr) {  ///insert node in tree
		if (key < parent->key) {
			parent->left = newNode;
		}
		else
			parent->right = newNode;
	}
	else {
		root = newNode;
	}
	insertFix(newNode);
}

template <class T, class V>
Node<T, V>* Map<T, V>::FindNode(T key) {
	Node<T, V>* current = root;
	if (current != nullptr) {
		while (current != nullptr) {
			if (key == current->key) {
				return current;
			}
			else {
				if (key < current->key) {
					current = current->left;
				}
				else
					current = current->right;
			}
		}
	}
	else throw out_of_range("There's no this element");
}

template <class T, class V>
Node<T, V>* Map<T, V>::FindValue(V value) {
	Node<T, V>* current = root;
	if (current != nullptr) {
		while (current != nullptr) {
			if (value == current->value) {
				return current;
			}
			else {
				if (value < current->value) {
					current = current->left;
				}
				else
					current = current->right;
			}
		}
	}
	else throw out_of_range("Empty"); 
}

template <class T, class V>
void Map<T, V>::remove(T key) {
	Node<T, V>* temp, * newNode2; ///temporary variables
	Node<T, V>* current = FindNode(key);
	if (current == nullptr) {
		throw out_of_range("Empty");
	}
	if (current->left == nullptr || current->right == nullptr) {
		temp = current;
	}
	else {
		temp = current->right;
		while (temp->left != nullptr) temp = temp->left;
	}

	if (temp->left != nullptr) {
		newNode2 = temp->left;
	}
	else {
		newNode2 = temp->right;
	}

	if (temp->parent != nullptr) {
		if (newNode2 != nullptr) {
			newNode2->parent = temp->parent;
		}
		if (temp == temp->parent->left) {
			temp->parent->left = newNode2;
		}
		else
			temp->parent->right = newNode2;
	}
	else newNode2 = root;

	if (temp != current) {
		current->key = temp->key;
		current->value = temp->value;
	}
	if (temp->color == false) {
		FixDelete(newNode2, temp->parent);
	}
	delete temp;
}

template <class T, class V>
void Map<T, V>::FixDelete(Node<T, V>* current, Node<T, V>* fixParent) {
	while (current != root && current->getColor() == false) {
		if (current == fixParent->left) {
			Node<T, V>* temp = fixParent->right;
			if (temp->getColor() == true) {
				temp->color = false;
				fixParent->color = true;
				LeftRotate(fixParent);
				temp = fixParent->right;
			}
			if (temp->left->getColor() == false && temp->right->getColor() == false) {
				temp->color = true;
				current = fixParent;
			}
			else {
				if (temp->right->color == false) {
					temp->left->color = false;
					temp->color = true;
					RightRotate(temp);
					temp = fixParent->right;
				}
				temp->color = fixParent->color;
				fixParent->color = false;
				current->color = false;
				LeftRotate(fixParent);
				current = root;
			}
		}
		else {
			Node<T, V>* temp = fixParent->left;
			if (temp->color == true) {
				temp->color = false;
				fixParent->color = true;
				RightRotate(fixParent);
				temp = fixParent->left;
			}
			if (temp->right->getColor() == false && temp->left->getColor() == false) {
				temp->color = true;
				current = fixParent;
			}
			else {
				if (temp->left->color == false) {
					if (temp->right != nullptr) {
						temp->right->color = false;
					}
					temp->color = true;
					LeftRotate(temp);
					temp = fixParent->left;
				}
				temp->color = fixParent->color;
				fixParent->color = false;
				temp->left->color = false;
				RightRotate(fixParent);
				current = root;
			}
		}
	}
}

template <class T, class V>
void Map<T, V>::Clear() { ///Recursive In-Order Travers
	root->clearNode();
	root = nullptr;
}
