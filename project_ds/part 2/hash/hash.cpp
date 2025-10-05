#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>

#include "../basics/basics.hpp"
#include "hash.hpp"

// used to check during recursion of menuHash () whether the Hash table 

bool hashflag = false;

const int buckets = 11;

std :: vector <HashNode * > hashTable[buckets];

// insert a new HashNode into the Hash table

bool insert (std :: string date, float temp) {
	HashNode * node = search (date);							// search if node with given date already exists
	if (node != nullptr) {
		modify (date, temp);									// if it exists then update its temp value to the new temp value
		return true;											// return true indicating successful insertion
	}
	node = new HashNode;										// otherwise create a new node
	node->date = date;
	node->temp = temp;
	int hashVal = calcHash (date);
	hashTable[hashVal].push_back (node);						// insert it into the correct vector of Hash table
	node = search (date);										// check if it was inserted correctly
	if (node != nullptr) return true;							// if it was return true indicating successful insertion
	return false;												// else return false indicating unsuccessful insertion
}

// read the file and insert a node per line of data, then close the file

bool createHash (void) {
	std :: ifstream file;
	file.open ("./data/ocean.csv", std :: ifstream :: in);		// open a stream from ocean.csv
	if (!file.good ()) {										// if the stream did not open successfully then exit after appropriate message, otherwise continue reading from it
		std :: cout << "\nUnable to read file.";
		exit (false);
	}
	std :: string line;
	getline (file, line);										// ignore the first line which contains the titles
    while (getline (file, line)) {								// get a line from ocean.csv per loop until EOF character is found
		std :: stringstream row (line);							// convert said line into a stream
		std :: string date;
		std :: string tmpstr;
        getline (row, date, ',');								// extract from said stream the date in string form
		getline (row, tmpstr, ',');								// extract from said stream the temperature in string form
		float temp = stof (tmpstr);								// convert temperature in string form to float
		bool flag = insert (date, temp);						// insert new element in Hash table with the date and temperature extracted from ocean.csv
        if (!flag) {											// if it was not then exit after appropriate message, otherwise continue the while loop
			std :: cout << "\nAn error occurred whilst inserting nodes in the Hash table.";
			exit (false);
		}
	}
	file.close ();												// close the stream from ocean.csv					
	return true;												// return true indicating successful initialization of date sorted AVL tree
}

// calculate the ascii sum % buckets of a date

int calcHash (std :: string date) {
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		sum += int (date.at (i));								// calculate the ascii value of each character inside date, and add it to sum
	}
	return sum % buckets;
}

// print the dates inside the buckets of Hash table (inspired by friend and colleague Konstantinos Markakis @ CEID)

void printBuckets (void) {
	std :: cout << std :: endl;
	for (int i = 0; i < buckets; i++) std :: cout << " ------------";
	std :: cout << std :: endl;
	for (int i = 0; i < buckets; i++) std :: cout << " |bucket" << std :: setfill (' ') << std :: setw (4) << i + 1 << '|';
	std :: cout << std :: endl;
	for (int i = 0; i < buckets; i++) std :: cout << " ------------";
	std :: cout << std :: endl;
	int maxSize = hashTable[0].size ();
	for (int i = 1; i < buckets; i++) {
		if (hashTable[i].size () > maxSize) maxSize = hashTable[i].size ();
	}
	for (int i = 0; i < maxSize; i++) {
		for (int j = 0; j < buckets; j++) {
			std :: vector <HashNode * > vctr = hashTable[j];
			HashNode * node = vctr[i];
			if (i < hashTable[j].size ()) std :: cout << ' ' << std :: setfill (' ') << std :: setw (12) << node->date;
		}
		std :: cout << std :: endl;
		for (int j = 0; j < buckets; j++) {
			std :: vector <HashNode * > vctr = hashTable[j];
			HashNode * node = vctr[i];
			if (i < hashTable[j].size ()) std :: cout << ' ' << std :: setfill (' ') << std :: setw (12) << std :: fixed << std :: setprecision (2) << node->temp;
		}
		std :: cout << '\n' << std :: endl;
	}
}

// find the temperature of a record given that record's date

HashNode * search (std :: string date) {
	int hashVal = calcHash (date);
	for (std :: vector <HashNode * > :: iterator itr = hashTable[hashVal].begin(); itr < (hashTable[hashVal]).end (); itr++) {
		HashNode * node = * itr;
		if (node->date == date) return node;				// if the node is found then the method returns a pointer to that node
	}
	return nullptr;											// if the node is not found then the method returns a null pointer indicating an unsuccessful search
}

// replace the value oldTemp with newTemp, of a node given its date

bool modify (std :: string date, float temp) {
	HashNode * node = search (date);						// search if node exists
	if (node == nullptr) return false;						// if node does not exist return false
	node->temp = temp;										// else change his temp value to the new temp
	return true;											// return true indicating successful modification
}

// erase a node from Hash table given its date

bool erase (std :: string date) {
	int hashVal = calcHash (date);
	for (std :: vector <HashNode * > :: iterator itr = hashTable[hashVal].begin(); itr < (hashTable[hashVal]).end (); itr++) {
		HashNode * node = * itr;
		if (node->date == date) {							// if the node with the correct date is found
			hashTable[hashVal].erase (itr);					// erase said node from vector
			return true;									// return true indicating successful erasure
		}
	}
	return false;											// otherwise return false indicatin unsuccessful erasure
}

// print all options available for Hash table

void hashOptions (void) {
    std :: cout << " <1> Print the dates inside each bucket." << std :: endl;
    std :: cout << " <2> Search record's temperature based on date." << std :: endl;
	std :: cout << " <3> Insert new record in Hash table." << std :: endl;
    std :: cout << " <4> Modify existing record's temperature based on date." << std :: endl;
    std :: cout << " <5> Erase record based on date." << std :: endl;
    std :: cout << " <6> Go Back.\n" << std :: endl;
    std :: cout << "Option: ";
}

// execute option 1 of hashOptions () - print every date inside Hash table

void hashOption1 (void) {
	space ();
	auto start = clk::now ();
	printBuckets ();
	auto end = clk::now ();
	ms duration = std :: chrono :: duration_cast<ms>(end - start);
    std :: cout << "\nExecution time: " << duration.count() << " milliseconds." << std :: endl;

}

// execute option 2 of hashOptions () - search

void hashOption2 (void) {
	space ();
	std :: string date;
	float temp;
	std :: cout << "\nPlease specify date - <format> month/day/year: ";
	std :: cin >> date;
	date = check (date);
	auto start = clk::now ();
	HashNode * node = search (date);
	auto end = clk::now ();
	if (node == nullptr) std :: cout << "\nDate not recorded." << std :: endl;
	else {
		std :: cout << "\nThe temperature at " << node->date << " is " << node->temp << " deg C." << std :: endl;
		us duration = std :: chrono :: duration_cast<us>(end - start);
        std :: cout << "\nExecution time: " << duration.count() << " microseconds." << std :: endl;
	}
}

// execute option 3 of hashOptions () - insert

void hashOption3 (void) {
	space ();
	std :: string date;
	float temp;
	bool flag = false;
	std :: cout << "\nPlease specify date - <format> month/day/year: ";
	std :: cin >> date;
	date = check (date);
	std :: cout << "\nPlease specify new temperature - deg C: ";
	std :: cin >> temp;
	auto start = clk::now ();
	flag = insert (date, temp);
	auto end = clk::now ();
	if (!flag) std :: cout << "\nUnsuccessful insertion of new record. Specified date already exists." << std :: endl;
	else {
		std :: cout << "\nSuccessful insertion of new record > date: " << date << ", temperature: " << temp << " deg C." << std :: endl;
		us dur = std :: chrono :: duration_cast <us> (end - start);
		std :: cout << "\nExecution time: " << dur.count () << " microseconds." << std :: endl;
	}
}

// execute option 4 of hashOptions () - modify

void hashOption4 (void) {
	space ();
	std :: string date;
	float temp;
	bool flag = false;
	std :: cout << "\nPlease specify date - <format> month/day/year: ";
	std :: cin >> date;
	date = check (date);
	std :: cout << "\nPlease specify new temperature - deg C: ";
	std :: cin >> temp;
	auto start = clk::now ();
	flag = modify (date, temp);
	auto end = clk::now ();
	if (!flag) std :: cout << "\nDate not recorded." << std :: endl;
	else {
		std :: cout << "\nSuccessful temperature modification." << std :: endl;
		std :: cout << "\nRecord > date: " << date << " - temperature: " << temp << " deg C." << std :: endl;
		us duration = std :: chrono :: duration_cast<us>(end - start);
        std :: cout << "\nExecution time: " << duration.count() << " microseconds." << std :: endl;
	}
}

// execute option 5 of hashOptions () - erase

void hashOption5 (void) {
	space ();
	std :: string date;
	bool flag = false;
	std :: cout << "\nPlease specify date - <format> month/day/year: ";
	std :: cin >> date;
	date = check (date);
	auto start = clk::now ();
	flag = erase (date);
	auto end = clk::now ();
	if (flag) {
		std :: cout << "\nSuccessful erasure of record." << std :: endl;
		us duration = std :: chrono :: duration_cast<us>(end - start);
        std :: cout << "\nExecution time: " << duration.count() << " microseconds." << std :: endl;
	} else std :: cout << "\nDate not recorded." << std :: endl;
}

// menu of Hash table

void menuHash (void) {
	space ();
	if (!hashflag) {
		hashflag = createHash ();
		if (hashflag) std :: cout << "\nSuccessful creation of Hash table." << std :: endl;
	}
	std :: string sel;
    std :: cout << "\nPlease select an option from the following:\n" << std :: endl;
	hashOptions ();
	std :: cin >> sel;
	while (sel != "1" && sel != "2" && sel != "3" && sel != "4" && sel != "5" && sel != "6") {
		space();
        std :: cout << "\nOption unavailable. Please select again:\n" << std :: endl;
        hashOptions ();
        std :: cin >> sel;
    }
	switch (stoi (sel)) {
		case 1 : {
			hashOption1 ();
			break;
		}
		case 2 : {
			hashOption2 ();
			break;
		}
		case 3 : {
			hashOption3 ();
			break;
		}
		case 4 : {
			hashOption4 ();
			break;
		}
		case 5 : {
			hashOption5 ();
			break;
		}
		case 6 : {
			hashflag = false;
			for (std :: vector <HashNode *> vctr : hashTable) vctr.clear ();
			return;
		}
	}
	menuHash ();
}

// main to debug the source code inside hash.cpp

// int main (void) {menuHash (); return 0;}	