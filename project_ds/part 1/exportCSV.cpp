#include <string>
#include <fstream>
#include "readFile.cpp"

void exportCSV(data measurements)
{
    // Create an output filestream object
    std::ofstream myCSV("updatedOcean.csv");

    // Send column names to the stream
    for(int i = 0; i < measurements.categories.size(); ++i)
    {
        myCSV << measurements.categories[i];
        if(i != measurements.categories.size() - 1) myCSV << ","; // No comma at end of line
    }
    myCSV << "\n";

    // Send data to the stream
    for(int i = 0; i < measurements.date.size(); ++i)
    {
        myCSV << measurements.date[i] << "," << measurements.temp[i] << "," << measurements.phosphate[i] << "," << measurements.silicate[i] << "," << measurements.nitrite[i] << "," << measurements.nitrate[i] << "," << measurements.salinity[i] << "," << measurements.oxygen[i];
        myCSV << "\n";
    }


    // Close the file
    myCSV.close();
}
