#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "../../basics/basics.hpp"
#include "../shared/shared.hpp"

// used to check during recursion of menuDate () whether the AVL tree exists or not

bool dateflag = false;

// search for temp value inside node->temp vector

bool searchTemp (AVLNode * node, float temp) {
	bool flag = false;
    if (node == nullptr) flag = false;                          // guard clause - check if node exists
    for (float flt : node->temp) {
        if (flt == temp) flag = true;							// if temp is found inside node's temp vector, then the method returns true
    }
    return flag;												// if after the for loop the method has not returned true, then it automatically returns false
}

// insert a new temp value inside node->temp vector, if it does not exist already

bool insertTemp (AVLNode * node, float temp) {
    if (node == nullptr) return false;                          // guard clause - check if node exists
    else if (searchTemp (node, temp)) return false;				// check if temp already exists inside node's temp vector
	else node->temp.push_back (temp);							// if temp does not exist inside node's temp vector then insert it at the end
	return true;
}

// print all values inside node->temp vector

void printTemps (AVLNode * node) {
    if (node == nullptr) return;                          		// guard clause - check if node exists
    std :: cout << std :: setw(5) << std :: setfill('0') << std :: fixed << std :: setprecision(2) << node->temp[0] << " deg C";
    for (int i = 1; i < node->temp.size (); i++) std :: cout << ", " << std :: setw(5) << std :: setfill('0') << std :: fixed << std :: setprecision(2) << node->temp[i] << " deg C";
    std :: cout << '.';
}

// convert string date into a modified int for use as key

int convert (std :: string date) {
    std :: string newdate = "01234567";
    newdate.at (0) = date.at (6);
    newdate.at (1) = date.at (7);
    newdate.at (2) = date.at (8);
    newdate.at (3) = date.at (9);
    newdate.at (4) = date.at (0);
    newdate.at (5) = date.at (1);
    newdate.at (6) = date.at (3);
    newdate.at (7) = date.at (4);
    return stoi	(newdate);
}

// insert a new AVLNode into the date Sorted AVL tree

bool insertNode (std :: string date, float temp) {
	int key = convert (date);														// since AVl is ordered by keys, match key with the modified version of date
	AVLNode * node = search (key);													// search if node with given date already exists
	if (root != nullptr && node == nullptr) return false;							// check if AVL tree was initialized correctly
	else if (node != nullptr && node->key == key) insertTemp (node, temp);			// if node already exists then update its temp vector
	else node = create (node, date, temp, key);										// else create a new node and insert it into the AVL tree
	balPath (node);																	// rebalance the first node found unbalanced in path from node to root
	node = search (node->key);														// search if node was inserted correctly
	if (node != nullptr) return true;												// if it was then return true indicating successful insertion
	return false;																	// otherwise return false indicating unsuccessful insertion
}

// read the file and insert a node per line of data, then close the file

bool createDate (void) {
    std :: ifstream file;
	file.open ("./data/ocean.csv", std :: ifstream :: in);							// open a stream from ocean.csv
	if (!file.good ()) {															// if the stream did not open successfully then exit after appropriate message, otherwise continue reading from it
		std :: cout << "\nUnable to read file.";
		exit (false);
	}
	std :: string line;
	getline (file, line);															// ignore the first line which contains the titles
    while (getline (file, line)) {													// get a line from ocean.csv per loop until EOF character is found
		std :: stringstream row (line);												// convert said line into a stream
		std :: string date;
		std :: string tmpstr;
        getline (row, date, ',');													// extract from said stream the date in string form
		getline (row, tmpstr, ',');													// extract from said stream the temperature in string form
		float temp = stof (tmpstr);													// convert temperature in string form to float
        bool flag = insertNode (date, temp);										// insert new element in date sorted AVL tree with the date and temperature extracted from ocean.csv and initialize the value of flag based on whether it was inserted correctly
		if (!flag) {																// if it was not then exit after appropriate message, otherwise continue the while loop
			std :: cout << "\nAn error occurred whilst inserting nodes in the AVL tree.";
			exit (false);
		}
	}
	file.close ();																	// close the stream from ocean.csv					
	return true;																	// return true indicating successful initialization of date sorted AVL tree
}

// traverse the date sorted AVL tree in order and print the data of each node

int iotDate (AVLNode * node, int counter) {
    if (node == nullptr) return counter;											// if node does not exist, return counter through recursion to count up all the nodes
    counter = iotDate (node->l, counter);											// visit left child of node first
    std :: cout << "node # " << std :: setfill ('0') << std :: setw (4) << counter++ << " > date: " << node->date[0] << " -> temperature(s): ";
    printTemps (node);
    std :: cout << std :: endl;
    counter = iotDate (node->r, counter);											// visit right child of node last
    return counter;																	// return counter through recursion to count up all the nodes
}

// wrapper method of iotDate (AVLNode * node, int counter) so that it starts from root and counts from 1

void iotDate (void) {
    iotDate (root, 1);
}

// replace oldTemp inside node->temp vector with newTemp, if it exists

bool modifyTemp (int key, float oldTemp, float newTemp) {
    AVLNode * node = search (key);
    if (node == nullptr) return false;												// guard clause - check if node exists
    if (node->key != key) return false;												// guard clause - check if node found is correct
    if (!searchTemp (node, oldTemp)) return false;									// guard clause - check if oldTemp exists inside vector temp of node
    for (int i = 0; i < node->temp.size (); i++) {				
        if (node->temp[i] == oldTemp) {												// if oldTemp is found
            node->temp[i] = newTemp;												// update value of oldTemp with newTemp
			return true;															// return true indicating successful modification
        }
    }
    return false;
}

// erase a node from the AVL tree and then rebalance if needed

bool erase (int key) {
    AVLNode * node = search (key);
    if (node == nullptr || root == nullptr || node->key != key) return false;       // null node
    if (node->r == nullptr && node->l == nullptr) {                                 // leaf node
        if (node == root) root = nullptr;                                           // leaf node = root (single node in AVL tree)
        else {                                                                      // leaf node != root
            if (node->p->r == node) node->p->r = nullptr;
            else node->p->l = nullptr;
        }
    } else if (node->r != nullptr && node->l == nullptr) {                          // node with only right child
        if (node == root) {
            root = node->r;
            node->r->p = nullptr;
        } else if(node->p->r == node) {
            node->p->r = node->r;
            node->r->p = node->p;
        } else if(node->p->l == node) {
            node->p->l = node->r;
            node->r->p = node->p;
        }
    } else {                                                                        // node with at least left child
        if (node->r != nullptr) {                                                   // node with both left and right child
            AVLNode * left = node->r;
            while (left->l != nullptr){
                left = left->l;
            }
            left->l = node->l->r;
            if (node->l->r != nullptr) node->l->r->p = left;
            node->l->p = node->p;
            node->l->r = node->r;
            node->r->p = node->l;
        }
        if (node == root) {                                                         // node with only left child
            root = node->l;
            node->l->p = nullptr;
        } else if(node->p->r == node) {
            node->p->r = node->l;
            node->l->p = node->p;
        } else if(node->p->l == node) {
            node->p->l = node->l;
            node->l->p = node->p;
        }
    }
    balPath (node);                                                                 // balance path from node to root
    delete node;                                                                    // free memory taken up by node
    return true;																	// return true indicating successful erasure
}

// print all options available for date Sorted AVL trees

void dateOptions (void) {
    std :: cout << " <1> Traversal of AVL tree in order." << std :: endl;
    std :: cout << " <2> Search record's temperature based on date." << std :: endl;
    std :: cout << " <3> Insert new record in AVL tree." << std :: endl;
    std :: cout << " <4> Modify existing record's temperature based on date." << std :: endl;
    std :: cout << " <5> Erase record based on date." << std :: endl;
    std :: cout << " <6> Go back." << std :: endl;
    std :: cout << "\nOption: ";
}

// execute option 1 of dateOptions () - in order traversal

void dateOption1 (void) {
	space ();
    std :: cout << std :: endl;
    auto start = clk::now ();
    iotDate ();
    auto end = clk::now ();
    ms dur = std :: chrono :: duration_cast <ms> (end - start);
    std :: cout << "\nExecution time: " << dur.count () << " milliseconds." << std :: endl;
}

// execute option 2 of dateOptions () - search

void dateOption2 (void) {
	space ();
    std :: string date;
    std :: cout << "\nPlease specify date - <format> month/day/year: ";
    std :: cin >> date;
    date = check (date);
    int key = convert (date);
    auto start = clk::now ();
    AVLNode * node = search (key);
    auto end = clk::now ();
    if (node == nullptr) {
        std :: cout << "\nAn error occurred whilst searching the AVL tree." << std :: endl;
        exit(false);
    }
    else if (node->key != key) std :: cout << "\nDate not recorded." << std :: endl;
    else {
        std :: cout << "\nRecord > date: " << node->date[0] << " - temperature(s): ";
        printTemps (node);
		us dur = std :: chrono :: duration_cast <us> (end - start);
		std :: cout << "\n\nExecution time: " << dur.count () << " microseconds." << std :: endl;
    }
}

// execute option 3 of dateOptions () - insert

void dateOption3 (void) {
	space ();
    std :: string date;
    float temp;
    std :: cout << "\nPlease enter date of new record - <format> month/day/year: ";
    std :: cin >> date;
    date = check (date);
    std :: cout << "\nPlease enter temperature of new record - deg C: ";
    std :: cin >> temp;
    auto start = clk::now ();
    bool flag = insertNode (date, temp);
    auto end = clk::now ();
    if (!flag) std :: cout << "\nUnsuccessful insertion of new record." << std :: endl;
	else {
		std :: cout << "\nSuccessful insertion of new record > date: " << date << ", temperature(s): ";
		printTemps (search (convert (date)));
		us dur = std :: chrono :: duration_cast <us> (end - start);
		std :: cout << "\n\nExecution time: " << dur.count () << " microseconds." << std :: endl;
	}
}

// execute option 4 of dateOptions () - modify

void dateOption4 (void) {
	space ();
    std :: string date;
    float oldTemp;
    float newTemp;
    std :: cout << "\nPlease specify record's date - <format> month/day/year: ";
    std :: cin >> date;
    date = check (date);
    int key = convert (date);
	AVLNode * node = search (key);
	if (node == nullptr) {
		std :: cout << "\nAn error occurred whilst searching the AVL tree." << std :: endl;
		exit (false);
	} else if (node->key != key) {
		std :: cout << "\nDate not recorded." << std :: endl;
		return;
	}
	std :: cout << "\nRecord > date: " << date << " - temperature(s): ";
	printTemps (node);
	std :: cout << "\n\nPlease specify one of the temperatures above to modify: ";
	std :: cin  >> oldTemp;
	std :: cout << "\nPlease specify the new temperature: ";
	std :: cin  >> newTemp;
	auto start = clk::now ();
	bool flag = modifyTemp (key, oldTemp, newTemp);
	auto end = clk::now ();
	if (!flag) std :: cout << "\nUnsucessful temperature modification." << std :: endl;
	else {
		std :: cout << "\nSuccessful temperature modification." << std :: endl;
		std :: cout << "\nRecord > date: " << node->date[0] << " - temperature(s): ";
		printTemps (node);	
		us dur = std :: chrono :: duration_cast <us> (end - start);
		std :: cout << "\n\nExecution time: " << dur.count () << " microseconds." << std :: endl;
	}
}

// execute option 5 of dateOptions () - erase

void dateOption5 (void) {
	space ();
	std :: string date;
	std :: cout << "\nPlease specify date - <format> month/day/year: ";
	std :: cin  >> date;
	date = check (date);
	int key = convert (date);
	auto start = clk::now ();
	bool flag = erase (key);
	auto end = clk::now ();
	if(!flag) std :: cout << "\nDate not recorded." << std :: endl;
	else {
		std :: cout << "\nSuccessful erasure of specified record." << std :: endl;
		us dur = std :: chrono :: duration_cast <us> (end - start);
		std :: cout << "\nExecution time: " << dur.count () << " microseconds." << std :: endl;
	}
}

// menu of date sorted AVL tree

void menuDate (void) {
	space ();
	if (!dateflag) {
		dateflag = createDate ();
		if (dateflag) std :: cout << "\nSuccessful creation of AVL tree sorted by date." << std :: endl;
	}
    std :: string sel;
	std :: cout << "\nPlease select an option from the following:\n" << std :: endl;
    dateOptions ();
    std :: cin >> sel;
    while (sel != "1" && sel != "2" && sel != "3" && sel != "4" && sel != "5" && sel != "6") {
		space ();
        std :: cout << "\nOption unavailable. Please select again:\n" << std :: endl;
        dateOptions ();
        std :: cin >> sel;
    }
    switch (stoi (sel)) {
        case 1 : {
            dateOption1 ();
            break;
        }
        case 2 : {
            dateOption2 ();
            break;
        }
        case 3 : {
            dateOption3 ();
            break;
        }
        case 4 : {
            dateOption4 ();
            break;
        }
        case 5 : {
            dateOption5 ();
            break;
        }
        case 6 : {
			dateflag = false;
			root = nullptr;
			return;
		}
    }
    menuDate ();
}

// main to debug the source code inside date.cpp

// int main (void) { menuDate (); return 0;}