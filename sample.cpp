#include <bits/stdc++.h>
using namespace std;

void merge(vector<int> &arr, int s, int m, int e) {
    int i = s, j = m + 1;
    vector<int> temp;
    while(i <= m && j <= e) {
        if(arr[i] < arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }
    while(i <= m) temp.push_back(arr[i++]);
    while(j <= e) temp.push_back(arr[j++]);
    int k = 0;
    for(int i = s; i <= e; i++) arr[i] = temp[k++];
    return;
}

void mSort(vector<int> &arr, int s, int e) {
    if(s >= e) return;
    int m = (s + e) / 2 - (e - s + 1) % 2;
    mSort(arr, s, m);
    mSort(arr, m + 1, e);
    merge(arr, s, m, e);
    return;
}

int main() {
    vector<int> arr = {10, 5, 2, 0, 7, 6, 4};
    queue<int> q;
    for(int i = 0; i < arr.size(); i++) q.push(arr[i]);
    while(!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    return 0;
}