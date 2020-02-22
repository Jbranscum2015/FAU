/*
Name: Jared Branscum          Z#: 23353586
Course: Data Structures
Professor: Dr. Mehrad Nojoumian
Due Date: 11/15/17              Due Time: 11:59 P.M.
Total Points: 100
Assignment 3

Description: double_linked_list implements a double linked list that creates "n" nodes, deletes a node in the end, and inserts a node at the beginning
*/

#include <iostream>
using namespace std;

//defines parameters for double linked lsit
struct dlinklist {
	int data;
	struct dlinklist * right;
	struct dlinklist * left;
};
typedef struct dlinklist node;
node * start = NULL; //global variable: points to first element in the list
int nodectr = 0; //global variable: number of nodes in the list
//function prototypes
node * getnode();
void create_list(const int &);
void delete_node_at_end();
void insert_at_beg();

int main() {
	int i; //number of elements in the list
	cout << "How many elements are you adding to your list? ";
	cin >> i;
	cout << "Creating list ... " << endl;

	create_list(i);
	cout << endl << "Double linked list of " << i << " elements: ";
	node * temp = start;
	while (temp != NULL) { //prints the list
		cout << temp->data << " ";
		temp = temp->right;
	}  
	delete_node_at_end();//deletes the last node in the list
	temp = start;
	cout << endl << "This is the current double linked list: ";
	while (temp != NULL) {//prints the list
		cout << temp->data << " ";
		temp = temp->right;
	}
	cout << endl;
	insert_at_beg();//inserts a node at the beginning of the list
	temp = start;
	cout << endl << "This is the current double linked list: ";
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->right;
	}
	cout << endl;
	return 0;
}
//adds node to list
node * getnode() {
	node * newnode;
	newnode = (node *)malloc(sizeof(node));
	cout << endl << "Enter data: ";
	cin >> newnode->data;
	newnode->left = NULL;
	newnode->right = NULL;
	nodectr++;
	return newnode;
}
//creates double linked list
void create_list(const int & x) {
	node *newnode;
	node * temp;
	for (int i = 0; i < x; i++) {
		newnode = getnode();
		if (start == NULL) {//case if list is empty
			start = newnode;
		}
		else {
			temp = start;
			while (temp->right != NULL) {//shifts pointers left
				temp = temp->right;
			}
			temp->right = newnode;
			newnode->left = temp;
		}
	}
}
//deletes the last node in the list
void delete_node_at_end() {
	node *temp;
	if (start == NULL) {//case if empty list
		cout << endl << "Empty List" << endl;
		return;
	}
	else {
		temp = start;
		while (temp->right != NULL) {//shifts pointers left
			temp = temp->right;
		}
		temp->left->right = NULL;
		nodectr--;
		free(temp);//deallocate memory to temp
		cout << endl << endl << "The last node is deleted" << endl;
	}
}
//inserts node at the beginning of the list
void insert_at_beg() {
	node *newnode;
	newnode = getnode();
	if (start == NULL) {//case if list is empty
		start = newnode;
		return;
	}
	else {//sets newnode pointers to start and vice versa, then sets newnode as the start of the linked list
		start->left = newnode;
		newnode->right = start;
		start = newnode;
	}
	cout << endl << "The node was inserted into the beginning of the list" << endl;

}
