## 26th July 2026

## Find smallest missing positive - Using numbers as index

- BF: sort, find smallest, O(nlogn)
- Optimise: Observe that we are only concerned for elements from 1 to n(size of the array), (smallest positive will be from these only). Elements before 0 and after n will never contribute to the answer.
- Example: Consider array 7,8,9,10,11. Its 5 sized, least positive not there is 1. Second example would be 1,-1,2, 3, 4. Least not present would be 5.
- So make a boolean array of size 1 to n, and for each number you get, mark corresponding index as True when found.
- Least index as False would be the answer. Takes O(n) extra space.
- Code: https://leetcode.com/problems/first-missing-positive/

- More Optimal approach: use numbers as index. Its a common pattern, also used in finding duplicates. When you encounter a number, take abs(number) go to number - 1 index and mark it as negative. We take abs as number might already be marked negative when we encounter it. Then after all operations the number positive + 1 would be the answer. The only catch is mark each non positive number and each number > n as 1. Also have a flag as onePresent to know if 1 was present in the actual array, compute this in a different loop. If not return 1 as answer. If present lookk for other numbers using this algorithm.

```cpp
int firstMissingPositive(vector<int>& nums) {
    int n = nums.size();
    int onePresent = false; // flag for presence of 1

    //loop for marking numbers <= 0 and numbers > n as 1, also for checking one present
    for(int i = 0; i < n; i++) {
        if(nums[i] == 1) onePresent = true;
        if(nums[i] <= 0 || nums[i] > n) nums[i] = 1;
    }

    // check if one wasnt present only
    if(!onePresent) return 1;

    // loop for marking abs(ele - 1) index as negative
    for(int i = 0; i < n; i++) {
        int indexToMarkNeg = abs(nums[i]) - 1;

        // do not mark if already negative
        if(nums[indexToMarkNeg] > 0) nums[indexToMarkNeg] = -1 * nums[indexToMarkNeg];
    }

    // check for least positive number present
    for(int i = 0; i < n; i++) {
        if(nums[i] > 0) return i + 1; //as no number - 1 made it negative, so number is answer
    }

    return n + 1; // all numbers were negative, so n + 1 is answer.

}
```
