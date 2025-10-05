#include <iostream>

#include "basics.hpp"

// return the value num - 48

int num (int num) {
    return num - 48;
}

// print a line of '=' characters with width equal to the max width of printing elements

void space (void) {
	std :: cout << std :: endl;
	for (int i = 0; i < 143; i++) std :: cout << '=';
	std :: cout << std :: endl;
}

// check if date value is valid and has the correct format

std :: string check (std :: string date) {
	int day = 0;
	int month = 0;
    if (date.size () == 10) {																	// get month in integer form if month in correct format
		if (isdigit (date.at (0)) && isdigit (date.at(1))) month = num (date.at (0)) * 10 + num (date.at (1));
	}
    if (date.size () == 10) {         												        	// get day in integer form if day in correct format
		if (isdigit (date.at (3)) && isdigit (date.at(4))) day = num (date.at (3)) * 10 + num (date.at (4));
	}
    while (month < 1 || month > 12 || day < 1 || day > 31 || (month == 2 && day > 28)           // check if (01 < month < 12) or if (01 < day < 31) or if (month = 02 and day > 28)
    || date.size () != 10 || date.at (2) != '/' || date.at (5) != '/') {        				// check if date size != 10 or if date divided with '/' character
        std :: cout << "\nInvalid date. Please enter date again - <format> month/day/year: ";
        std :: cin >> date;
		day = 0;
		month = 0;
		if (date.size () > 2) {																	// update the month value for the next while loop using the new date value
			if (isdigit (date.at (0)) && isdigit (date.at(1))) month = num (date.at (0)) * 10 + num (date.at (1));
		}
        if (date.size () > 5) {         												        // update the day value for the next while loop using the new date value
			if (isdigit (date.at (3)) && isdigit (date.at(4))) day = num (date.at (3)) * 10 + num (date.at (4));
		}         
    }
    return date;
}

// wrapper method of exit (int exit_code) that prints a notification on the terminal

void exit (bool flag) {
    std :: cout << " The application will now terminate." << std :: endl;
    if (flag) exit(0);
	else exit(1);
}