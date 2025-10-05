int interpolationSearch(string key, vector<int>date, int n)
{
    cout<<"Searching date: "<< key << endl;

    int newKey = vecstoi(key);

    //InterpolationSearch Begins Here:

    // Find indexes of two corners

    int left = 0, right = (n - 1);

    // Since array is sorted, an element present
    // in array must be in range defined by corner
    while (left <= right && newKey >= date[left] && newKey <= date[right])
    {
        if (left == right)
        {
            if (date[left] == newKey) return left;
            return -1;
        }
        // Probing the position with keeping
        // uniform distribution in mind.
        int next = left + (((right - left) /
            (date[right] - date[left])) * (newKey - date[left]));

        // Condition of target found
        if (date[next] == newKey)
            return next;

        // If x is larger, x is in upper part
        if (date[next] < newKey)
            left = next + 1;

        // If x is smaller, x is in the lower part
        else
            right = next - 1;
    }
    return -1;
}
