#include <iostream>

#include "../basics/basics.hpp"
#include "../avl/date/date.hpp"
#include "../avl/temp/temp.hpp"
#include "../hash/hash.hpp"

void menuOptions1 (void) {
	std :: cout << " <1> Load data in AVL tree." << std :: endl;
	std :: cout << " <2> Load data in Hash table." << std :: endl;
	std :: cout << " <3> Exit the application." << std :: endl;
	std :: cout << "\nOption: ";
}

void menuOptions2 (void) {
	std :: cout << " <1> Date sorted AVL tree." << std :: endl;
	std :: cout << " <2> Temperature sorted AVL tree." << std :: endl;
	std :: cout << " <3> Go back." << std :: endl;
	std :: cout << "\nOption: ";
}

void menu (void) {
	std :: string sel1;
	std :: cout << "\nSelect an option from the following:\n" << std :: endl;
	menuOptions1 ();
	std :: cin >> sel1;
	while (sel1 != "1" && sel1 != "2" && sel1 != "3")	{
		space ();
		std :: cout << "\nOption Unavailable. Please Select Again:\n" << std :: endl;
		menuOptions1 ();
		std :: cin >> sel1;
	}
	switch (stoi (sel1)) {
		case 1: {
			space();
			std :: string sel2;
			std :: cout << "\nSelect AVL type:\n" << std :: endl;
			menuOptions2 ();
			std :: cin >> sel2;
			while (sel2 != "1" && sel2 != "2" && sel2 != "3")	{
				space ();
				std :: cout << "\nOption Unavailable. Please Select Again:\n" << std :: endl;
				menuOptions2 ();
				std :: cin >> sel2;
			}
			switch (stoi (sel2)) {
				case 1 : {
					menuDate ();
					break;
				}
				case 2 : {
					menuTemp ();
					break;
				}
				case 3 : break;
			}
			break;
		}
		case 2 : {
			menuHash ();
			break;
		}
		case 3 : {
			space ();
			std:: cout << "\nThis preview has come to an end.";
			exit (true);
		}
	}
	space ();
	menu ();
}

int main (void) {menu (); return 0;}