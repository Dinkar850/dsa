## 7th July

## Next Greater Element(NGE)

- for circular array
- start from last, remove all elements from stack that are smaller or equal to arr[index] where index = (i % n), and i ranges from {2n - 1, 0}. If stack is empty then arr[ind] has no greater element, else top of stack is next greater element. So update nge[i] = -1 if stack empty otherwise nge[i] = top of stack. Return first n elements of nge vector as answer.

```cpp
vector<int> nextGreaterElement(vector<int> &arr){
    int n = arr.size();
    vector<int>nge(2 * n); //its like consider array 1 2 3 4 so for circular: 1 2 3 4 1 2 3 4

    stack<int>st;
    for(int i = 2 * n - 1; i >= 0; i--) {
        int ind = i % n; //for circular array
        while(!st.empty() && arr[ind] >= st.top()) st.pop();
        if(st.empty()) nge[ind] = -1;
        else nge[ind] = st.top();
        st.push(arr[ind]);
    }
    vector<int> ans;
    for(int i = 0; i < n; i++) ans.push_back(nge[i]);
    return ans;
}
```

- similary you can find NSE by reversing the above condition of arr[ind] >= st.top() to arr[ind] <= st.top(), and you can also find PGE, PSE by starting from 0.

## 9th July

## Sum of subarray minimum (gfg)

- beautiful demonstration of use of NSE and PSE to calculate subarrays having minimum element as arr[i]
- for arr[i], total subarrays having minimum element as arr[i] are `(i - PSE[i]) * (NSE[i] - i)`
- reason: https://discuss.geeksforgeeks.org/comment/28ae4e63-ac77-4256-b2be-fcf81cc4c71a/practice
