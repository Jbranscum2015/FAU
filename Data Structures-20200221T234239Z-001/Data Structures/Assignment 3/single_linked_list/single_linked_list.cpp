/*
Name: Jared Branscum          Z#: 23353586
Course: Data Structures
Professor: Dr. Mehrad Nojoumian
Due Date: 11/15/17              Due Time: 11:59 P.M.
Total Points: 100
Assignment 3

Description: single_linked_list implements a single linked list that creates "n" nodes, deletes a node in the middle, and inserts a node in the middle
*/

#include <iostream>
using namespace std;
//defines parameters for double linked list
struct slinklist {
	int data;
	struct slinklist * next;
};
typedef struct slinklist node;
node * start = NULL; //global variable: points to first element in the list
int nodectr = 0; //global variable: number of nodes in the list
//function prototypes
node * getnode();
void create_list(const int &);
void delete_node_at_mid();
void insert_at_middle();

int main() {
	int i; //number of elements in the list
	cout << "How many elements are you adding to your list? ";
	cin >> i;
	cout << "Creating list ... " << endl;
	create_list(i);
	cout << endl << "Single linked list of " << i << " elements: ";
	node * temp = start;
	while (temp != NULL) { //prints the list
		cout << temp->data << " ";
		temp = temp->next;
	}
	delete_node_at_mid(); //delets a node in the middle of the list
	temp = start;
	cout << endl << "This is the current double linked list: ";
	while (temp != NULL) { //prints the list
		cout << temp->data << " ";
		temp = temp->next;
	}

	insert_at_middle(); //inserts a node in the middle of the list
	temp = start;
	cout << endl << "This is the current double linked list: ";
	while (temp != NULL) { //prints the list
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
	return 0;
}
//adds node to list
node * getnode() {
	node * newnode;
	newnode = (node *)malloc(sizeof(node)); //allocates memory to list
	cout << endl << "Enter data: ";
	cin >> newnode->data;
	newnode->next = NULL;
	nodectr++;
	return newnode;
}
//creates single linked list 
void create_list(const int & x) {
	node *newnode;
	node * temp;
	for (int i = 0; i < x; i++) {
		newnode = getnode();
		//case if list is empty
		if (start == NULL) {
			start = newnode;
		}
		else {
			//shifts the pointers for the new element added to the list
			temp = start;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newnode;
		}
	}
}
//deletes a node in the middle of the list
void delete_node_at_mid() {
	node *temp, *prev;
	int pos, ctr = 1;
	if (start == NULL) {//case if list is empty
		cout << endl << "Empty List" << endl;
		return;
	}
	cout << endl << "Enter position of node to delete from the middle: ";
	cin >> pos;
	if (pos > nodectr) { //case to check if pos exceeds possible nodes in the list
		cout << endl << "This node doesn't exist" << endl;
	}
	else if (pos > 1 && pos < nodectr) {//case to check if pos is not the first or last node
		temp = prev = start;
		while (ctr < pos) {
			prev = temp;
			temp = temp->next;
			ctr++;
		}
		prev->next = temp->next;
		nodectr--;
		free(temp);
		cout << endl << "The node was deleted" << endl;
	}
	else{
		cout << endl << "The position of the node cannot be deleted" << endl;
	}
}
//inserts a node into the middle of the list
void insert_at_middle() {
	node *newnode, *temp, *prev;
	int pos, ctr = 1;

	if (start == NULL) {//case if list is empty
		cout << endl << "Empty List" << endl;
		return;
	}
	cout << endl << "Enter the position to insert in the middle: ";
	cin >> pos;
	if (pos > 1 && pos < nodectr) {//case to check that pos is not at the first or last node
		newnode = getnode();
		temp = prev = start;
		while (ctr < pos) {//shifts the pointers preceding the position
			prev = temp;
			temp = temp->next;
			ctr++;
		}
		prev->next = newnode;
		newnode->next = temp;
	}
	else {
		cout << "The position " << pos << " is not a middle position" << endl;
	}
}