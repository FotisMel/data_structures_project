int binSearch(string key, vector<int>date, int left, int right)
{
    int newKey = vecstoi(key);
    if (right >= left) {
        int mid = left + (right - left) / 2;

        // If the element is present at the middle
        if (date[mid] == newKey)
            return mid;

        // If element is smaller than mid, then it can only be present in left subarray
        if (date[mid] > newKey)
            return binSearch(key, date, left, mid - 1);

        // Else the element can only be present in right subarray
        return binSearch(key, date, mid + 1, right);
    }
    //If the element is not found
    return -1;
}
