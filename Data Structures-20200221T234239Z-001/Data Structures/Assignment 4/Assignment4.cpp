/*
Name: Jared Branscum          Z#: 23353586
Course: Data Structures
Professor: Dr. Mehrad Nojoumian
Due Date: 11/30/17              Due Time: 11:59 P.M.
Total Points: 100
Assignment 4

Description: A queue using single linked list that has the functions insert, delete, and display. 
The program asks the user to insert data to create the linked list, then it runs the three functions.
*/

#include <iostream>
using namespace std;

//defines parameters for single linked list
struct slinklist {
	int data;
	struct slinklist * next;
};
typedef struct slinklist node;
node * start = NULL; //global variable: points to first element in the list
node * rear = NULL; //global variable: points to last element in the list
int nodectr = 0; //global variable: number of nodes in the list
//function prototypes
node * getnode();
void create_list(const int & x);
void insertQ();
void deleteQ();
void displayQ();

int main() {
	int i; //number of elements in the list
	cout << "How many elements are you adding to your list? ";
	cin >> i;
	cout << "Creating list ... " << endl;
	create_list(i);
	cout << endl << "Single linked list of " << i << " elements: ";
	displayQ();
	cout << endl;
	insertQ();
	deleteQ();
	cout << endl << "A node was added to the queue: ";
	displayQ();
	cout << endl;
	return 0;
}

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
			rear = newnode->next;
		}
	}
}
//inserts a node at the end of the queue
void insertQ() {
	node * newnode, * temp;
	newnode = getnode();
	if (start == NULL) {//case if list is empty
		start = newnode;
		rear = newnode->next;
		return;
	}
	else {
		//shifts the pointers for the new element added to the list
		temp = start;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		rear = temp->next = newnode; //adds newnode to queue
	}
}
//deletes a node at the beginning of the queue
void deleteQ() {
	node * temp = start;
	if (start = NULL) {
		cout << endl << "Empty queue";
		return;
	}
	else {
		start = temp->next; //points start to the next node
	}
}

void displayQ(){
	node * temp = start;
	while (temp != NULL) { //prints the list
		cout << temp->data << " ";
		temp = temp->next;
	}
}