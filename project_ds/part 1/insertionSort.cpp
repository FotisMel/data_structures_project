//Include Guards
#ifndef INSERTION_SORT
#define INSERTION_SORT

void insertionSort(vector<int> &sortingVec, vector<string> &date, vector<float> &temp, vector<float> &phosphate, vector<float> &silicate, vector<float> &nitrite, vector<float> &nitrate, vector<float> &salinity, vector<float> &oxygen) {
    //We sort according to the first argument.
    int i,j;
    int N = sortingVec.size();

    for(i=1; i<N; i++) {
        j = i; //The pos where the sorted part of the array ends.

        //insert vec[i] into the sorted part of the vector
        while (j > 0 && sortingVec[j] < sortingVec[j-1]) {
            swap(sortingVec[j], sortingVec[j-1]);

            //Swap the rest of the vectors accordingly
            swap(date[j], date[j-1]);
            swap(temp[j],temp[j-1]);
            swap(phosphate[j],phosphate[j-1]);
            swap(silicate[j],silicate[j-1]);
            swap(nitrite[j], nitrite[j-1]);
            swap(nitrate[j], nitrate[j-1]);
            swap(salinity[j], salinity[j-1]);
            swap(oxygen[j], oxygen[j-1]) ;

            j--;
        }
    }
}

void insertionSort(vector<float> &sortingVec, vector<string> &date, vector<float> &temp, vector<float> &phosphate, vector<float> &silicate, vector<float> &nitrite, vector<float> &nitrate, vector<float> &salinity, vector<float> &oxygen) {
    //We sort according to the first argument.
    int i,j;
    int N = sortingVec.size();

    for(i=1; i<N; i++) {
        j = i; //The pos where the sorted part of the array ends.

        //insert vec[i] into the sorted part of the vector
        while (j > 0 && sortingVec[j] < sortingVec[j-1]) {
            swap(sortingVec[j], sortingVec[j-1]);

            //Swap the rest of the vectors accordingly
            swap(date[j], date[j-1]);
            swap(temp[j],temp[j-1]);
            swap(phosphate[j],phosphate[j-1]);
            swap(silicate[j],silicate[j-1]);
            swap(nitrite[j], nitrite[j-1]);
            swap(nitrate[j], nitrate[j-1]);
            swap(salinity[j], salinity[j-1]);
            swap(oxygen[j], oxygen[j-1]) ;

            j--;
        }
    }
}
#endif // INSERTION_SORT
