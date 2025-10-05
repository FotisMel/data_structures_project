int BIS2(string key, vector<int>date, int n) //similar to BIS but now the sqrt multiplier "i" with powers of 2
{
    cout<<"Searching date: "<< key << endl;

    int newKey = vecstoi(key);

    int left = 0;
    int right = n -1;
    int size = right - left + 1;

    int next = (int)(size * ((double)(newKey - date[left]))/
        (date[right] - date[left])) +1;

    //if the Key is the last or the one before that, the fraction will be equal to 1 and the vector's index will be invalid
    if (next-2 == n-1)
    {
        if (newKey == date[date.size() - 1])
            return date.size() - 1;
    }

    // Since array is sorted, an element present
    // in array must be in range defined by corner
    if (newKey > date[date.size() - 1] || newKey < date[0] ) //Check if the key does not exceed or is inferior to the highest and lowest values.
    {
        return -1;
    }
    else
    {
        while(left<right && newKey != date[next])
        {
            int i = 0; //Multiplier of sqrts
            size = right - left;

            if (size<=5)
            {
                //if size is small, we do linear search
                for (int j = left; j <= right; j++)
                {
                    if (date[j] == newKey)
                    {
                        return j;
                    }
                }
				cout<<"LinearSearch failed"<<endl;
                return -1;
            }
            if (newKey >= date[next])
            {
                while(newKey > date[next + pow(2, i - 1)*(int)(sqrt(size)) - 1]) //We use pow(2, i - 1) here
                { i++; }

                right = next + (int)(pow(2, i - 1)*sqrt(size)) ; //We use pow(2, i - 1) here
                left = next + (int)(pow(2, i - 2)*sqrt(size)) ; //We use pow(2, i - 1) here
            }
            else if ( newKey < date[next] )
            {
                while(newKey < date[next - pow(2, i - 1)* (int)(sqrt(size))+ 1]) //We use pow(2, i - 1) here
                { i++; }

                right = next - (int)(pow(2, i - 2)*sqrt(size)) ; //We use pow(2, i - 1) here
                left = next - (int)(pow(2, i - 1)*sqrt(size)) ; //We use pow(2, i - 1) here
            }

            if (left != right) //if size is not 1
            {
                //Update next
                next = (int) (left + ((right - left +1) * (newKey - date[left]) / (date[right] - date[left]))) - 1;
            }
            else //if size is 1
            {
                next = left;
            }
        }
    }

    if (newKey == date[next])//Check if we're inside bounds and if we have the correct data
    {
        return next;
    }
    else
    {
        cout<<"Error 404: Date not found"<<endl;
        cout<<"pos = "<< next <<endl;
        return -1;
    }
}
