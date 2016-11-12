#ifndef PA2_H
#define PA2_H
#include <iostream>

#include "stdio.h"

using namespace std;

void command(int argc, char *argv[]);

// Linked List class called "List"
class List{
private:


	// Creates a node struct
    typedef struct node{
        string data;
        node *next;
        bool isFree;
    }* nodePtr;

    nodePtr head;
    nodePtr curr;
    nodePtr temp;

// Declares public functions that are a part of the List class
// which can be used on objects of the List type in the source file
public:
    List();
	void addNode(string addData);
    bool bestFit(string programName, int pagesUsed);
    bool worstFit(string programName, int pagesUsed);
	void replaceProgram(string programName, int index);
    bool removeProgram(string dataToRemove);
    void fragments();
    void printList();
	int bestIndex;
	int worstIndex;
	bool print;
};


// Constructor for the List object
List::List(){
    head = NULL;
    curr = NULL;
    temp = NULL;
}

// This function takes in a string, and adds a node to the linked list that
// contains this string as its stored data
void List::addNode(string addData){
    nodePtr n = new node;
    n->next = NULL;
    n->data = addData;
    if (head != NULL){
        curr = head;
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = n;
    }
    else {
        head = n;
    }
}

// The bestFit function takes in a program name and the pages a program uses
// as its parameters and determines the beginning index for the best fit
// algorithm

//Checks to see if the best fit is a viable option to insert the specified program
bool List::bestFit(string programName, int pagesUsed) {

	int count = 0;
	int min = 32;
	int beginning = 0;
	int startCount = 0;

	curr = head;

	while(curr->next != NULL) {

		//Checks the curr spot to see if the program being added is already a program
		if (curr->data == programName){
			cout << "Error. Program " << programName << " already running." << endl;
			return false;
		}

		//If a spot contains free it starts the placement count
		if (curr->data == "Free"){
			//beginning = startCount;
			// While the data at a node is "Free", begin looking for the beginning
			// of the worst fit index and its range, and then continue searching
			// for other potential worst fit ranges.
			while (curr->data == "Free"){
				if (curr->next != NULL){
					count++;
					curr = curr->next;
					startCount++;
				}
				else{
					break;
				}
			}

			// Finds the index
			if (count >= pagesUsed) {

				if (count < min) {
					min = count;
					beginning = startCount-count;
					bestIndex = beginning;
				}

			}

		}

		else if (curr->next != NULL){
			curr = curr->next;
			startCount++;
		}
		count = 0;

	}

	//returns if the best fit is true(works) or false(doesn't work)
	if (min >= pagesUsed){
		return true;
	}
	else{
		return false;
	}
}

// Worst fit function looks for the worst possible placement for the given
// program name of given page length
bool List::worstFit(string programName, int pagesUsed){

	int max = 0;
	int count = 1;

	curr = head;
	int beginning = 0;
	int startCount = 0;

	while(curr->next != NULL){

		// If the program already exists, return false.
		if (curr->data == programName){
			cout << "Error. Program " << programName << " already running." << endl;
			return false;
		}

		//Start counting at the first free spot
		if (curr->data == "Free"){
			beginning = startCount;

			// While the data at a node is "Free", begin looking for the beginning
			// of the worst fit index and its range, and then continue searching
			// for other potential worst fit ranges.
			while (curr->data == "Free"){

				//
				if (curr->next != NULL){
					count++;
					curr = curr->next;
					startCount++;

				}
				else{
					break;
				}

				if (count > max) {
					max = count;
					worstIndex = beginning;
				}
			}
			count = 0;

		}

		else if (curr->next != NULL){
			curr = curr->next;
			startCount++;
		}

	}

	// Returns true if the algorithm is successful, and false if otherwise
	if (max >= pagesUsed ){
		return true;
	}
	else{
		return false;
	}
}


// This function conducts the replacement of data of each node by taking in the
// index at which a change needs to be made, and placing the given
// program name into that particular node
void List::replaceProgram(string programName, int initialIndex){
    curr = head;
	print = false;
    int count = 0;

    while (count < initialIndex){
        curr = curr->next;
        count++;
    }
	if (curr->data == "Free"){
		curr->data = programName;
		print = true;
	}
}


// This function goes through the list and searches for the program given as
// a parameter to be deleted. When deleting the program, the node's data is then
// set to be "Free"
bool List::removeProgram(string dataToRemove){
    curr = head;
    bool result = false;

	// Loop through the entire linked list to search for the program
    for (int i = 0; i < 32; i++){
        if (curr->data == dataToRemove){
            curr->data = "Free";
            result = true;
        }

        // If there's something there that isn't NULL or the input data
        // to remove, move on
        if(curr->next != NULL){
            curr = curr->next;
        }
    }

	// Return true if the data is found, false otherwise
    if(result){
        return result;
    }
    else{
        return result;
    }
}

// Prints the number of memory fragments that exist at any moment
void List::fragments() {

    curr = head;
    bool b = true;
    string name;
    int fragments = 0;

	// Loops until the end of the list
    while (curr != NULL){

		// Checks to see if the curr data is free and the comparison factor
		// b is true. If so, increase the number of fragments, set b to be false
        if (curr->data == "Free" && b){
            fragments++;
            b = false;
            curr = curr->next;

        }

		// If curr data is free and b is false, move on to the next node
        else if (curr->data == "Free" && b == false){
            curr = curr->next;
        }

		// Set b = true and move on to the node if none of the other cases are
		// fulfilled.
        else{
            b = true;
            curr = curr->next;
        }

    }
    cout << "There are " << fragments << " fragment(s)" << endl;

}

// Prints the linked list using nested for loops.
void List::printList(){
    curr = head;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 8; j++){
            if (curr->data == "Free"){
                cout << curr->data << " ";
                curr = curr->next;
            }
            else{
                cout << curr->data << "   ";
                curr = curr->next;
            }
        }
        cout << "\n";
    }
}


#endif
