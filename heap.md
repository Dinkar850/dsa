## 18th July

- after solving quite a bunch of questions, i observed that when there is a situation where you need to access the top after some pops, you dont pop and store in some other pq and then push it back. You just create a pq where you push a new element after popping the ones you dont need anymore, then you access the required element. Okay?

- this is mostly the pattern that you will observe
- you can see today's POTD and the ones with meetings in potds of this month

## 1st August

## Heap

- a complete binary tree where if the parent node is always greater than its children, then the tree is a max heap
- a complete binary tree where if the parent node is always smaller than its children is a min heap
- a complete binary tree is the one whos array representation has no gaps
- a complete binary tree can also be defined as the one which is a full binary tree uptil height - 1 and then fills up the last height from left to right
- a full binary tree is the one which has max number of nodes filled up till height h and inserting another node would lead to increase in height. Total nodes in height h is ${2 ^ {h + 1} - 1}$

## Array Representation of a heap

- the array rep of heap would be like:
  - node at index i
  - left child at index $2 * i$
  - right child at index $2 * i + 1$
  - parent at index $i / 2$

## Insertion in a heap

- TC: ${O(log{n})}$
- init a heap array with first element as 0 for making the heap 1 indexed
- insert the element at last
- then check with the parent, if the element is greater than parent, swap, then check with the next parent again and swap if greater, repeat this process
- as we are checking with parent and swapping only at i / 2 positions, we would be doing one insertion operation in logn time and inserting n nodes would take ${O(n * log{n})}$ time
- this process is a top-down approach of insertion

```cpp
void insertHeap(vector<int> &heap, int val) {
    heap.push_back(val);
    int ind = heap.size() - 1;
    while(ind > 1 && heap[ind / 2] < heap[ind]) {
        swap(heap[ind /2], heap[ind]);
        ind /= 2;
    }
}
```

## Deletion in a heap

- TC: ${O(log{n})}$
- we can only delete the root element of the heap
- by deleting the root element only, we get access to the topmost or maximum element in the max heap, minimum element in the min heap
- for deletion, swap the last element of the heap with first one
- then move first element in the correct position by following the below procedure:
  - access the node's left and right children, if one of them doesnt exist mark it as INT_MIN
  - check if the parent is greater than the left and right child, if it is greater, then break
  - else swap the parent with the greater child and repeat the process
- this process is a bottom-up approach
- we also observe that in the first step when we swapped the last element with the first one, max element got at the last index
- if we do this process repeatedly we would get the max, then second max, then third and so on in the last, second last and third last indices, thereby sorting the array in ascending order
- this is called heap sort

```cpp
void deleteHeap(vector<int> &heap, int n) {
    swap(heap[1], heap[n]);
    n--;
    int ind = 1;
    while(true) {
        int left = INT_MIN;
        int right = INT_MIN;
        if(2 * ind <= n) left = heap[2 * ind];
        if(2 * ind + 1 <= n) right = heap[2 * ind + 1];
        if(left == INT_MIN && right == INT_MIN) break;
        int swap_ind = (left >= right) ? 2 * ind : 2 * ind + 1;
        if(heap[ind] < heap[swap_ind]) {
            swap(heap[ind], heap[swap_ind]);
            ind = swap_ind;
        }
        else break;
    }
}
```

## Heapify

- creation of heap by inserting one by one was one way
- other is forming a heap by copying the array and then changing it to actual heap by using certain operations called heapifying
- similar to deletion process, starting from back, compare left and right child, choose the greater one, compare the greater one with parent, if greater than parent, swap, else break
- also if left and right child is INT_MIN, then break

```cpp
void heapify(vector<int> &heap) {
    int n = heap.size() - 1;
    for(int i = n / 2; i >= 1; i--) {
        int ind = i;
        while(true) {
            int left = INT_MIN;
            int right = INT_MIN;
            if(2 * ind <= n) left = heap[2 * ind];
            if(2 * ind + 1 <= n) right = heap[2 * ind + 1];
            if(left == INT_MIN && right == INT_MIN) break;
            int swap_ind = (left >= right) ? 2 * ind : 2 * ind + 1;
            if(heap[ind] < heap[swap_ind]) {
                swap(heap[i], heap[swap_ind]);
                ind = swap_ind;
            }
            else break;
        }
    }
}
```

## Heap Sort

- heapify array or create a heap thru array
- delete elements one by one till n >= 1 starting from n = arr.size() - 1
- the resultant array will be the sorted one
- its unstable by nature due to arbitrary shifts while insertion and deletion in the array

```cpp
#include <bits/stdc++.h>
using namespace std;
void insertHeap(vector<int> &heap, int val) {
    heap.push_back(val);
    int ind = heap.size() - 1;
    while(ind > 1 && heap[ind / 2] < heap[ind]) {
        swap(heap[ind /2], heap[ind]);
        ind /= 2;
    }
}

void deleteHeap(vector<int> &heap, int n) {
    swap(heap[1], heap[n]);
    n--;
    int ind = 1;
    while(true) {
        int left = INT_MIN;
        int right = INT_MIN;
        if(2 * ind <= n) left = heap[2 * ind];
        if(2 * ind + 1 <= n) right = heap[2 * ind + 1];
        if(left == INT_MIN && right == INT_MIN) break;
        int swap_ind = (left >= right) ? 2 * ind : 2 * ind + 1;
        if(heap[ind] < heap[swap_ind]) {
            swap(heap[ind], heap[swap_ind]);
            ind = swap_ind;
        }
        else break;
    }
}

void heapify(vector<int> &heap) {
    int n = heap.size() - 1;
    for(int i = n / 2; i >= 1; i--) {
        int ind = i;
        while(true) {
            int left = INT_MIN;
            int right = INT_MIN;
            if(2 * ind <= n) left = heap[2 * ind];
            if(2 * ind + 1 <= n) right = heap[2 * ind + 1];
            if(left == INT_MIN && right == INT_MIN) break;
            int swap_ind = (left >= right) ? 2 * ind : 2 * ind + 1;
            if(heap[ind] < heap[swap_ind]) {
                swap(heap[i], heap[swap_ind]);
                ind = swap_ind;
            }
            else break;
        }



    }
}
int main() {
    vector<int> arr = {8, 5, 2, 0, 6, 4, 9};
    vector<int> heap;
    heap.push_back(0);
    heap.insert(heap.begin() + 1, arr.begin(), arr.end());
    // for(int i: arr) insertHeap(heap, i);
    heapify(heap);
    for(int n = arr.size(); n >= 1; n--) deleteHeap(heap, n);
    for(int i = 0; i < heap.size(); i++) cout << heap[i] << " ";
    return 0;
}
```

## Priority Queues

- instead of conventional FIFO, elements with higher priority are served first that is removed first
- one way can be smaller elements having higher priority
- another can be larger elements having higher priority
- implementing a PQ with conventional array would take O(n) time whereas using min Heap for first case and max Heap for second, it can be done in O(logn ) time
