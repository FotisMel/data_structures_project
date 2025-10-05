//Include Guards
#ifndef READFILE
#define READFILE

#include <iostream>
#include <regex>
#include <iterator>
#include <fstream>
#include <string>

using namespace std;

struct data{
    vector<string>categories;
    vector<string>date;
    vector<float>temp;
    vector<float>phosphate;
    vector<float>silicate;
    vector<float>nitrite;
    vector<float>nitrate;
    vector<float>salinity;
    vector<float>oxygen ;
    bool success;
};

data readFile()
{
    fstream inputFile("ocean.csv",ios::in);    // Input file stream object

    data measurements;

    if (inputFile.good())    // Check if file exists and then open it.
    {
        regex regPatern("\(?:,|\n|^)([^,\n]*|(?:\n|$))");
        //match_results //It is automatically filled by regex_match, regex_search or a regex_iterator
        smatch match; //We need a match object, also smatch is an instance of match_results, so it gets updated the same way

        string line; int column=0;
        while(getline(inputFile,line))
        {
            auto lineBegin = sregex_iterator(line.begin(), line.end(), regPatern); //start regex stream iterator, has a special state end of stream iterator
            auto lineEnd = sregex_iterator(); //end of stream iterator, value is returned by the default constructor

            int rows = 0;
            for (sregex_iterator regIt = lineBegin; regIt != lineEnd; ++regIt)
            {
                match = *regIt;
                if (column==0) measurements.categories.push_back(match[1]);
                else
                {
                    if (rows == 0) measurements.date.push_back(match[1]);//if rows == 0, it's date
                    else if (rows == 1) measurements.temp.push_back(stof(match[1]));//if rows == 1, then it's temp
                    else if (rows == 2) measurements.phosphate.push_back(stof(match[1]));//if rows == 2, then it's phosphate
                    else if (rows == 3) measurements.silicate.push_back(stof(match[1]));//if rows == 3, then it's silicate
                    else if (rows == 4) measurements.nitrite.push_back(stof(match[1]));//if rows == 4, then it's nitrite
                    else if (rows == 5) measurements.nitrate.push_back(stof(match[1]));//if rows == 5, then it's nitrate
                    else if (rows == 6) measurements.salinity.push_back(stof(match[1]));//if rows == 6, then it's salinity
                    else if (rows == 7) measurements.oxygen .push_back(stof(match[1]));//if rows == 7, then it's oxygen
                }
                rows++;
            }
            column++;
        }
        measurements.success = true;
    }
    else
    {
        measurements.success = false;
        cout<<"Unable to load file"<<endl;
    }
    return measurements;
}
#endif // End definition of READFILE
