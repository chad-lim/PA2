#include <iostream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include "stdio.h"
#include "pa2.h"

using namespace std;

int main(int argc, char *argv[]){

	// Takes command line arguments
	command(argc, argv);


	// Creates a new Linked List object and initializes it to
	// have 32 nodes that store "Free"
	List list;
    for (int i = 0; i < 32; i++){
        list.addNode("Free");
    }
    cout << endl;



	/* MENU */
    cout << "    1. Add a program\n    2. Kill a program\n    3. Fragmentation\n    4. Print memory\n    5. Exit" << endl;

    string programName = "";

    char userChoice;
	int programSize;
	int pagesUsed;

	// Do-While loop that continuously asks the user for a response based on the
	// menu items until they select "5"
    do{

    	cout << "choice - ";
        cin >> userChoice;

        switch(userChoice){


			// Deals with adding programs to the linked list, which includes
			// finding the best/worst index and adding the provided program
            case '1':
                cout << "Program name - ";
                cin >> programName;

				// Free is an invalid input. The program exits if this is input
				// as a program name.
				if (programName == "Free"){
					cout << "\"Free\" is not a valid program name. Exiting." << endl;
					exit(EXIT_SUCCESS);
				}

                cout << "Program size (KB) - ";
                cin >> programSize;

				// Rounds up to find the amount of pages used per KB
                pagesUsed = ceil((double)programSize/4);

				// Do worst fit
				if(string(argv[1]) == "worst"){

					// Checks the boolean value given by worstFit to determine
					// if it needs to continue replacing programs
					if(list.worstFit(programName, pagesUsed)){

						// Sets the amount of times the replace program loop
						// will iterate.
						int initialIndex = list.worstIndex;
						int finalIndex = initialIndex + pagesUsed;

						// Replaces the programs at each specified index
						while(initialIndex < finalIndex){
							list.replaceProgram(programName, initialIndex);
							initialIndex++;
						}
						cout << "Program " << programName << " added successfully: " << pagesUsed << " page(s) used." << endl;


					}
					else{

					}

				}
				// Do best fit
				else {

					// Checks the boolean value given by bestFit to determine
					// if it needs to continue replacing programs
					if(list.bestFit(programName, pagesUsed)){

						// Sets the amount of times the replace program loop
						// will iterate.
						int initialIndex = list.bestIndex;
						int finalIndex = initialIndex + pagesUsed;

						// Replaces the programs at each specificed index
						while(initialIndex < finalIndex){
							list.replaceProgram(programName, initialIndex);
							initialIndex++;

						}
						if(list.print){
							cout << "Program " << programName << " added successfully: " << pagesUsed << " page(s) used." << endl;
						}
						else{
							cout << "Error. Not enough memory for Program " << programName << endl;
						}
					}
					else{

					}

			}
			break;

			// Removes programs from the linked list based on user input
			//and replaces them with "Free"
            case '2':
                cout << "Program name - ";
                cin >> programName;

				// Free is an invalid input. The program will exit when free is
				// entered
				if (programName == "Free"){
					cout << "\"Free\" is not a valid program name. Exiting." << endl;
					exit(EXIT_SUCCESS);
				}

				// Removes the program of the given name if the removeProgram
				// function returns true. If not, it is determined that the
				// given program is unavailable to be killed
				if(list.removeProgram(programName)){
	            	cout << "Program " << programName << " killed successfully." <<endl;
				}
				else{
					cout << "Program " << programName << " does not exist and cannot be killed." <<endl;
				}
                break;

			// Prints the number of fragments at a particular moment
            case '3':
				list.fragments();
				break;

			// Prints the linked list
            case '4':
				list.printList();
                break;

			// Exits the program
            case '5':
                exit(EXIT_SUCCESS);

			// Default option for if the user inputs a choice that is not 1-5
			default:
				cout << "Please enter a valid option from the menu" << endl;

        }
    }
    while(userChoice != 5);

	return 0;
}

// Takes in the command line arguments
void command(int argc, char *argv[]){

	// Two arguments are required, the name of the program and "best" or "worst"
	if (argc != 2){
        cout << "Incorrect number of arguments. Exiting." << endl;
        exit(EXIT_SUCCESS);
    }
    else if (string(argv[1]) == "worst"){
        cout << "Using worst fit algorithm" << endl;

    }
    else if (string(argv[1]) == "best"){
        cout << "Using best fit algorithm" << endl;

    }
	// If the arguments are not "best" or "worst" exit the program
    else {
        cout << "Invalid input. Exiting." << endl;
        exit(EXIT_SUCCESS);
    }
}
