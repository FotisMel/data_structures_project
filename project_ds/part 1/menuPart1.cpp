#include <iostream>
#include <chrono>
#include <math.h> // sqrt
#include "readFile.cpp"
#include "printData.cpp"
#include "menuSorting.cpp"
#include "menuSearching.cpp"
#include "exportCSV.cpp"

using namespace std;
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::nanoseconds ns;

void menuPart1(void)
{
    data measurements = readFile();
    if (measurements.success == true)
    {
        menuSorting();
        //menuSearching(); We call menuSearching from menuSorting()

        string selection;
        cout<<"\nExport CSV (y/n)"<<endl;
        cout<<"Choice: ";
        cin >> selection;
        while(selection != "y" && selection != "n" && selection != "Y" && selection != "N"){
            cout<<"\nOption Unavailable. Please Select Again:\n"<<endl;
            cout<<"Export CSV (y/n)"<<endl;
            cout<<"Choice: ";
            cin >> selection;
        }
        if(selection == "Y" || selection == "y")
        {
            cout<<"exporting to csv..."<<endl;
            exportCSV(measurements);
        }
    }
    else{//if file was not read correctly
        cout<<"Error File Not Found"<<endl;
    }
}
