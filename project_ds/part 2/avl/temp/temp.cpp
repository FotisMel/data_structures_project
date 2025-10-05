#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "../../basics/basics.hpp"
#include "../shared/shared.hpp"

// used to check during recursion of menuTemp () whether the AVL tree exists or not

bool tempflag = false;

// search for date value inside node->date vector

bool searchDate (AVLNode * node, std :: string date) {
	bool flag = false;
    if (node == nullptr) flag = false;                          // guard clause - check if node exists
    for (std :: string str : node->date) {
        if (str == date) flag = true;							// if date is found inside node's date vector, then the method returns true
    }
    return flag;												// if after the for loop the method has not returned true, then it automatically returns false
}

// insert a new date value inside node->date vector, if it does not exist already

bool insertDate (AVLNode * node, std :: string date) {
    if (node == nullptr) return false;                          // guard clause - check if node exists
    else if (searchDate (node, date)) return false;				// check if date already exists inside node's date vector
	else node->date.push_back (date);							// if date does not exist inside node's date vector then insert it at the end
	return true;
}

// print all values inside node->date vector

void printDates (AVLNode * node) {
    if (node == nullptr) return;                          		// guard clause - check if node exists
    std :: cout << node->date[0];
    for (int i = 1; i < node->date.size (); i++) std :: cout << ", " << node->date[i];
    std :: cout << '.';
}

// insert a new AVLNode into the temp sorted AVL tree

bool insertNode (float temp, std :: string date) {
	int key = temp * 100;														// since AVl is ordered by keys, match key with temp * 100, eliminating decimal digits
	AVLNode * node = search (key);												// search if node with given date already exists
	if (root != nullptr && node == nullptr) return false;						// check if AVL tree was initialized correctly
	else if (node != nullptr && node->key == key) insertDate (node, date);		// if node already exists then update its temp vector
	else node = create (node, date, temp, key);									// else create a new node and insert it into the AVL tree
	balPath (node);																// rebalance the first node found unbalanced in path from node to root
	node = search (key);														// check if node was inserted correctly
	if (node != nullptr) return true;											// if it was return true indicating successful insertion
	return false;																// else return false indicating unsuccessful insertion
}

// read the file and insert a node per line of data, then close the file

bool createTemp (void) {
	std :: ifstream file;
	file.open ("./data/ocean.csv", std :: ifstream :: in);						// open a stream from ocean.csv
	if (!file.good ()) {														// if the stream did not open successfully then exit after appropriate message, otherwise continue reading from it
		std :: cout << "\nUnable to read file.";
		exit (false);
	}
	std :: string line;
	getline (file, line);														// ignore the first line which contains the titles
    while (getline (file, line)) {												// get a line from ocean.csv per loop until EOF character is found
		std :: stringstream row (line);											// convert said line into a stream
		std :: string date;
		std :: string tmpstr;
        getline (row, date, ',');												// extract from said stream the date in string form
		getline (row, tmpstr, ',');												// extract from said stream the temperature in string form
		float temp = stof (tmpstr);												// convert temperature in string form to float
        bool flag = insertNode (temp, date);									// insert new element in temperature sorted AVL tree with the date and temperature extracted from ocean.csv
        if (!flag) {															// if it was not then exit after appropriate message, otherwise continue the while loop
			std :: cout << "\nAn error occurred whilst inserting nodes in the AVL tree.";
			exit (false);
		}
	}
	file.close ();																// close the stream from ocean.csv					
	return true;																// return true indicating successful initialization of date sorted AVL tree
}

// traverse the Date Sorted AVL tree in order and print the data of each node

int iotTemp (AVLNode * node, int counter) {
    if (node == nullptr) return counter;										// if node does not exist, return counter through recursion to count up all the nodes
    counter = iotTemp (node->l, counter);										// visit left child of node first
    std :: cout << "node # " << std :: setfill ('0') << std :: setw (4) << counter++ << " > temp: " << std :: setfill ('0') << std :: setw (5) << std :: fixed << std :: setprecision (2) << node->temp[0] << " -> date(s): ";
    printDates (node);
    std :: cout << std :: endl;
    counter = iotTemp (node->r, counter);										// visit right child of node last
    return counter;																// return counter through recursion to count up all the nodes
}

// wrapper method of iotTemp (AVLNode * node, int counter) so that it starts from root and counts from 1

void iotTemp (void) {
    iotTemp (root, 1);
}

// find the lowest value inside the AVL tree

AVLNode * findMin (void) {
	AVLNode * node = root;														// point pointer to root
	if (node == nullptr) return nullptr;										// if node does not exist, then return nullptr indicating that the AVL tree has not yet been initialized
	while (node->l != nullptr) node = node->l;									// traverse the AVL tree from root to the left furthest node
	return node;																// return said node
}

// find the highest value inside the AVL tree

AVLNode * findMax (void) {
	AVLNode * node = root;														// point pointer to root
	if (node == nullptr) return nullptr;										// if node does not exist, then return nullptr indicating that the AVL tree has not yet been initialized
	while (node->r != nullptr) node = node->r;									// traverse the AVL tree from root to the right furthest node
	return node;																// return said node
}

// print all actions available for temp sorted AVL trees

void tempOptions (void) {
	std :: cout << " <1> Traversal of AVL tree in order." << std :: endl;
    std :: cout << " <2> Find dates of minimum temperature." << std :: endl;
    std :: cout << " <3> Find dates of maximum temperature." << std :: endl;
	std :: cout << " <4> Insert new record in AVL tree." << std :: endl;
    std :: cout << " <5> Go back." << std :: endl;
    std :: cout << "\nOption: ";
}

// execute option 1 of dateOptions () - in order traversal

void tempOption1 (void) {
	space ();
    std :: cout << std :: endl;
    auto start = clk::now ();
    iotTemp ();
    auto end = clk::now ();
    ms dur = std :: chrono :: duration_cast <ms> (end - start);
    std :: cout << "\nExecution time: " << dur.count () << " milliseconds." << std :: endl;
}

// execute option 2 of tempOptions () - find minimum temp

void tempOption2 (void) {
	space ();
	auto start = clk::now ();
	AVLNode * node = findMin ();
	auto end = clk::now ();
	if (node == nullptr) {
		std :: cout << "\nAn error occurred whilst navigating the AVL tree." << std :: endl;
		exit (false);
	}
	std :: cout << "\nRecord > minimum temperature: " << node->temp[0] << " deg C - date(s): ";
	printDates (node);
	us dur = std :: chrono :: duration_cast <us> (end - start);
	std :: cout << "\n\nExecution time: " << dur.count () << " microseconds." << std :: endl;
}

// execute option 3 of tempOptions () - find maximum temp

void tempOption3 (void) {
	space ();
	auto start = clk::now ();
	AVLNode * node = findMax ();
	auto end = clk::now ();
	if (node == nullptr) {
		std :: cout << "\nAn error occurred whilst navigating the AVL tree." << std :: endl;
		exit (false);
	}
	std :: cout << "\nRecord > maximum temperature: " << node->temp[0] << " deg C - date(s): ";
	printDates (node);
	us dur = std :: chrono :: duration_cast <us> (end - start);
	std :: cout << "\n\nExecution time: " << dur.count () << " microseconds." << std :: endl;
}

// execute option 4 of tempOptions () - insert

void tempOption4 (void) {
	space ();
    std :: string date;
    float temp;
    std :: cout << "\nPlease enter date of new record - <format> month/day/year: ";
    std :: cin >> date;
    date = check (date);
    std :: cout << "\nPlease enter temperature of new record - deg C: ";
    std :: cin >> temp;
    auto start = clk::now ();
    bool flag = insertNode (temp, date);
    auto end = clk::now ();
    if (!flag) std :: cout << "\nUnsuccessful insertion of new record." << std :: endl;
	else {
		std :: cout << "\nSuccessful insertion of new record > temperature: " << temp << ", date(s): ";
		printDates (search (temp * 100));
		us dur = std :: chrono :: duration_cast <us> (end - start);
		std :: cout << "\n\nExecution time: " << dur.count () << " microseconds." << std :: endl;
	}
}

// menu of temp sorted AVL tree

void menuTemp (void) {
	space ();
	if (!tempflag) {
		tempflag = createTemp ();
		if (tempflag) std :: cout << "\nSuccessful creation of AVL tree sorted by temperature." << std :: endl;
	}
	std :: string sel;
	std :: cout << "\nPlease select an option from the following:\n" << std :: endl;
	tempOptions ();
	std :: cin >> sel;
	while (sel != "1" && sel != "2" && sel != "3" && sel != "4" && sel != "5") {
		space ();
        std :: cout << "\nOption unavailable. Please select again:\n" << std :: endl;
        tempOptions ();
        std :: cin >> sel;
    }
	switch (stoi (sel)) {
		case 1 : {
			tempOption1 ();
			break;
		}
		case 2 : {
			tempOption2 ();
			break;
		}
		case 3 : {
			tempOption3 ();
			break;
		}
		case 4 : {
			tempOption4 ();
			break;
		}
		case 5 : {
			tempflag = false;
			root = nullptr;
			return;
		}
	}
	menuTemp ();
}

// main to debug the source code inside temp.cpp

// int main (void) {menuTemp (); return 0;}