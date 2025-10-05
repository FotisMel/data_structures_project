void countSort(vector<float> array,vector<string> &v,int size) {

  int arr[array.size()];
  for (int i = 0; i < array.size(); i++){
    arr[i] = (int) (array[i]*100);
  }

  int output[size];
  string soutput[size];
  int count[size];
  int max = arr[0];
  string smax = v[0];

      for (int i = 1; i < size; i++) {
        if (arr[i] > max)
          max = arr[i];
          smax = v[i];
      }

      for (int i = 0; i <= max; ++i) {
        count[i] = 0;
      }

      for (int i = 0; i < size; i++) {
        count[arr[i]]++;
      }

      for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
      }

      for (int i = size - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        soutput[count[arr[i]] - 1] = v[i];
        count[arr[i]]--;
      }

      for (int i = 0; i < size; i++) {
        arr[i] = output[i];
        v[i] = soutput[i];
      }
}
