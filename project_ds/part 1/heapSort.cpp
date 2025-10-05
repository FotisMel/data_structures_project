void max_heapify(vector<float>& arr, vector<string> &v, int i, int size_)
{
    int largest, l = (2*i) + 1, r = l + 1;

    if(l < size_ && arr[l] > arr[i])
        largest = l;
    else
        largest = i;

    if(r < size_ && arr[r] > arr[largest])
        largest = r;

    if(largest != i)
    {
        swap(arr[i], arr[largest]);
        swap(v[i], v[largest]);

        max_heapify(arr, v , largest, size_);
    }
}

void build_max_heap(vector<float>& arr,vector<string> &v)
{
    for(int i = (arr.size() / 2); i >= 0; i--)
    max_heapify(arr, v, i, arr.size());
}

void heapSort(vector<float>& arr,vector<string> &v)
{
   build_max_heap(arr,v);
   int sz = arr.size();
   for(int i = arr.size() - 1; i > 0; i--)
   {
        swap(arr[0], arr[i]);
        swap(v[0], v[i]);
        sz--;
        max_heapify(arr, v, 0, sz);
    }
}
