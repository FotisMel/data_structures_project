#define printCateg cout<<measurements.categories[0]<<"\t\t"; for(auto it = measurements.categories.begin()+1; it != measurements.categories.end(); it++) { cout << *it<<"\t"; } cout<<endl;

void printData(data measurements)
{
    //We use macros in order to minimize the chunk of code we need to call in order to print the categories each time.
    printCateg;
    for(int i=0;i<measurements.date.size();i++)
    {
        cout << measurements.date[i] << "\t" << measurements.temp[i] << "\t" << measurements.phosphate[i] << "\t" << measurements.silicate[i] << "\t" << measurements.nitrite[i] << "\t" << measurements.nitrate[i] << "\t" <<  measurements.salinity[i] << "\t" << measurements.oxygen [i] <<endl;
    }
}
