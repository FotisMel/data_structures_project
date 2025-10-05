vector<int> vecstoi(vector<string> date)
{
    vector<int> newDate;
    for (auto& str : date) {
        str.erase(std::remove(str.begin(), str.end(), '/'), str.end());
        newDate.push_back(stoi(str));
    }
    return newDate;
}
int vecstoi(string key)
{
    int newKey;
    key.erase(remove(key.begin(), key.end(), '/'), key.end()); //remove '/' from string
    newKey = stoi(key);
    return newKey;
}
