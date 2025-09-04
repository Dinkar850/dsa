## When to use which sort??

- General applications: Quick Sort
- Database sorting: Merge Sort (stability)
- Memory-constrained systems: Heap Sort
- Small datasets: Insertion Sort
- Integer sorting with known range: Count Sort
- Fixed-format data: Radix Sort
- use selection sort for minimal swaps that is when swapping is expensive for large objects
- use bubble sort for teaching purposes

## Bubble Sort

- TC: $${O(n ^ 2)}$$
- best case for this and all two below is ${O(n)}$ only.
- for i iterations from 0 to n - 1, loop j from 0 to n - i - 1 always and swap if arr[j] > arr[j + 1]

```cpp
void bubbleSort(vector<int>& arr) {
    // code here
    for(int i = 0; i < arr.size() - 1; i++) {
        for(int j = 0; j < arr.size() - i - 1; j++) {
            if(arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
        }
    }
}
```

- the sort is stable by default but if you change the strict equality to greater than or equal to, it will be unstable.

## Insertion Sort

- TC: $${O(n ^ 2)}$$
- our task is to find the right place to insert the current element. The right place will always be before that and after the operation the array before the current elment will always be sorted.

```cpp
void insertionSort(vector<int>& arr) {
    // code here
    for(int i = 1; i < arr.size(); i++) {
        int curr = arr[i];
        int j = i;
        while(j > 0 && arr[j - 1] > curr) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = curr;
    }
}
```

- stable by default but again if changing strict to greater than or equal to, it will be unstable.

## Selection Sort

- TC: $${O(n ^ 2)}$$
- we are going to find the minimum element in the array and swap it with the current element.
- we will assume that the array before the current element is always sorted.

```cpp
void selectionSort(vector<int> &arr) {
    // code here
    for(int i = 0; i < arr.size() - 1; i++) {
        int minInd = i;
        for(int j = i + 1; j < arr.size(); j++) {
            if(arr[j] < arr[minInd]) {
                minInd = j;
            }
        }
        swap(arr[i], arr[minInd]);
    }
}
```

- this sort is unstable. it is because lets assume we have 4, 8, 7, 6, 4, 3 here and then the first 4 will be swapped by last 3, and it will go after the second 4 changing the original order and making it unstable.

## Count Sort

- TC: ${O(3*n + max_element)}$
- SC: ${O(n + max_element)}$
- the idea is to count the number of elements less than or eqaul to a number at a particular index and then place the element at that index accordingly.
- like in the array: 5 2 3 2 1, there is no element smaller than 1, so 1 will be at index 0, then 2 elenents smaller than equal to 2, place 2 at index 1 and 2, and so on...
- the approach cud be counting the occurrences of each element by making a frequency array of size equal to the maximum element in the array, then calculating the cumulative sum of the frequency array and then placing the element at the index of the cumulative sum.
- like in the above example the freq array would be: 0 1 2 1 0 1 at index 0 1 2 3 4 5.
- cf array would be 0 1 3 4 4 5, so by taking element at each indx we say that 0 will be from index 0 to 0, 1 will be from 0 to 1, 2 will be from 1 to 3, and so on...
- but here we have no track that whether the 2 afterwards come before or the before one come at first making the sort unstable
- to make it stable again we follow another approach:
- we traverse the array from last to first and then as we get an element, we decrease one from the cf at that index and then place the element at the index = value at cf of that element, see the code:

```cpp
//find maxi:
int maxi = *max_element(arr.begin(), arr.end());
//make freq array:
vector<int>freq(maxi + 1, 0);
//fill freq array:
for(int i = 0; i < arr.size(); i++) {
    freq[arr[i]]++;
}

//make cf array:
vector<int> cf(maxi + 1, 0);
cf[0] = freq[0];
for(int i = 1; i <= maxi; i++) {
    cf[i] = cf[i - 1] + freq[i];
}

//traverse from end to beginning in the array, decrease once the value of cf at that index and place the element at that index ( = value of cf at that index after reducing):
vector<int>sorted_arr(arr.size(), 0);
for(int i = arr.size() - 1; i >= 0; i--) {
    cf[arr[i]]--;
    sorted_arr[cf[arr[i]]] = arr[i];
}
arr = sorted_arr;
```

- the count sort is not applicable where:
  - max element >>> n
  - n shud be comparable to max_element
  - n must not be double
  - n <= 10 ^ 6 as n is supposed to be an index
  - the differences among numbers shudnt be too much like 1 899 20 900.... for such cases use radix sort
  - so count sort is best in use cases where the above are not the conditions, as it sorts in linear time but with extra space. (best for sorting strings)
- for negative numbers you can normalize by adding the min element to each element, sort, and subtract the min element from each element again to obtain the original array

## Radix Sort

- TC: ${O(d * (n + k))}$
- SC: ${O(n + k)}$
- k is max element as in count sort above too but k is confined to 10 (base or radix of the numbers present in the array), so can be treated as constant
- d here is less than 20 for practical integers (it is the number of digits in the largest element)
- radix sort is all about applying count sort for as many times as the number of digits in the largest element
- the first pass is for the least significant digit, the second pass is for the second least significant digit and so on...
- the number of passes is equal to the number of digits in the largest element
- for example: given the array: `170, 45, 75, 90, 802, 2`
- max element: 802, so loop will go for three times that is pos = 1, 10 and 100
- first sort according to least significant digit or the last digit, for this we use the count sort making frequency array from 0 to 10 and updating count of those digits whose LSD is 0 to 10, here 170's LSD is 0, 45's is 5 and so on
- so the freq array would be: `2{170, 90}, 0, 2{802, 2}, 0, 0, 2{45, 75}, 0, 0, 0, 0`
- for doing this we use `freq[(arr[i] / pos) % 10]++` and then `cf[i] = cf[i - 1] + freq[i]`
- then we go across each element from last like in count sort and do cf[ind]-- and ans[cf[ind]] = arr[i] and copy each element from ans back to arr, where `ind = (arr[i] / pos) % 10`
- in first pass the array wud look like: `170, 90, 802, 2, 45, 75`
- for second pass, pos becomes 10 and we repeat the whole process again, and same for pos = 100, for pos = 1000, max / pos = 0, so we stop
- hence radix sort is more or less a safer version of count sort, as it also works for large gaps in numbers and also when k >> n
- this version of radix sort which takes in elements from last like cuont sort is also stable

```cpp
void countSort(int arr[], int n, int pos) {
    //init freq array of 10 (radix)
    vector<int> freq(10, 0);
    for(int i = 0; i < n; i++) {
        freq[(arr[i] / pos) % 10]++;
    }
    vector<int> cf(10, 0);
    cf[0] = freq[0];
    for(int i = 1; i < 10; i++) {
        cf[i] = cf[i - 1] + freq[i];
    }
    vector<int> ans(n);
    for(int i = n - 1; i >= 0; i--) {
        int ind = (arr[i] / pos) % 10;
        cf[ind]--;
        ans[cf[ind]] = arr[i];
    }
    //copying back ans to arr
    for(int i = 0; i < n; i++) arr[i] = ans[i];

}

void radixSort(int arr[], int n) {
    // finding max element
    int maxi = *max_element(arr, arr + n);

    // till pos is higher than max element
    for(int pos = 1; maxi / pos > 0; pos *= 10) {
        countSort(arr, n, pos);
    }
}
```

- dont use radix sort for floating point numbers as it will not work for them.
- dont use radix sort if the numbers or gaps is very less and the max element is also less. use normal count sort for that
- cant use when there arent natural representation of numbers being used
- variable length strings are not suppported by radix sort

## Shell Sort

- TC: $${O(n ^ 2)}$$
- same idea as insertion sort, but instead of comparing adjacent elements like arr[j - 1] with arr[j], compare arr[j - gap] with arr[j]
- this way we reduce the number of comparisons and hence the TC
- one way of assigning gap is to start with gap = n / 2 and then keep on dividing it by 2 until it becomes 1
- the gap is always the number of elements that are compared in each iteration
- the TC of shell sort depends on the assignment of gap but in the worst case it will be ${O(n ^ 2)}$ only
- in the code of insertion sort replace 1 by gap and then it will become shell sort
- it is unstable as due to different gaps, equal elements might be swapped in different iterations thus making one come before another even if it was later in the original sequence

```cpp
void sortArr(vector<int> &arr) {
    // code here
    int n = arr.size();
    int gap = n / 2;
    while(gap >= 1) {
        for(int i = gap; i < arr.size(); i++) {
            int curr = arr[i];
            int j = i;
            //instead of j > 0, use j - gap + 1 > 0, rest everywhere replace 1 by gap
            while(j - gap + 1 > 0 && arr[j - gap] > curr) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = curr;
        }
        gap /= 2;
    }
}
```

## Heap Sort

- TC: ${O(nlogn)}$
- SC: ${O(1)}$
- Refer to <a href="heap.md">Heap</a> for more details about heap and heap sort

## Quick Sort

- Worst Case TC: ${O(n ^ 2)}$
- Best Case TC: ${O(nlogn)}$
- Average Case TC: ${O(nlogn)}$
- Space Complexity: ${O(1)}$

- Worst case happens when the pivot is always the smallest or largest element of the array.
- Best case happens when the pivot is always the middle element of the array
- Average case happens when the pivot is always the median element of the array
- its unstable due to arbitrary partitioning of the array around the pivot
- In the code of quick sort, the pivot is conveniently the last element of the array. This can be changed to any other element of the array.
- The idea is to put all elements less than pivot to left and all elements greater than pivot to right of pivot. The pivot is then placed in the middle of the array and returned by the `partition` function.
- Then the new limits for quick sort becomes s, p - 1 and p + 1, e, where initially s was 0 and e was arr.size() - 1
- call quick sort recursively on these limits and return when s >= e
- example:
  - consider array: `10 5 2 0 7 6 4`
  - first s = 0, e = n - 1, that is qSort(arr, 0, n - 1) is called
  - init pivot as arr[e]
  - then init i = s - 1 and j = 0 to j < e, whenever you find an element less than pivot while traversing, incremenet i and swap that element with arr[i].
  - after this increment i again and swap the last element of array that was pivot and return i as the new pivot point or partition point
  - call qSort recusrively for `qSort(s, p - 1)` and `qSort(p + 1, e)`
  - when `s >= e`, return
  - so after first pass the array would look like` 2 0 4 10 5 7 6`, then you call `qSort(0, 1)` and `qSort(3, n - 1)` and `p = 2`.

```cpp
#include <bits/stdc++.h>
using namespace std;

int partition(vector<int> &arr, int s, int e) {
    int pivot = arr[e];
    int i = s - 1;
    for(int j = s; j < e; j++) {
        if(arr[j] < pivot) swap(arr[++i], arr[j]);
    }
    swap(arr[++i], arr[e]);
    return i;
}

void qSort(vector<int> &arr, int s, int e) {
    if(s >= e) return;
    int p = partition(arr, s, e);
    qSort(arr, s, p - 1);
    qSort(arr, p + 1, e);
    return;
}

int main() {
    vector<int> arr = {10, 5, 2, 0, 7, 6, 4};
    qSort(arr, 0, arr.size() - 1);
    for(int i = 0; i < arr.size(); i++) cout << arr[i] << " ";
    return 0;
}
```

## Merge Sort

- TC: ${O(nlogn)}$
- SC: ${O(n)}$
- stable sorting algo
- merge sort is a divide and conquer algorithm. It divides the input array into two halves, calls itself for the two halves, and then merges the two sorted halves.
- the two halves would be `mSort(s, m)` and `mSort(m + 1, e)` where `m = (s + e) / 2`
- merge by using the strategy of storing the min of two lists in temp

```cpp
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
    mSort(arr, 0, arr.size() - 1);
    for(int i = 0; i < arr.size(); i++) cout << arr[i] << " ";
    return 0;
}
```

## Intro Sort

- used by inbuilt sorting functionality of most of the programming languages
- its a hybrid sort that uses Quick Sort for average cases, falls back to Heap Sort for worst cases and uses insertion Sort for cases where the array is of less size
- it fallsback to heap instead of merge sort as heap uses no extra space.
