4/10/2026

## Valid Parenthesis String

```cpp
class Solution {
public:
    bool checkValidString(string s) {
        // Greedy appraoch - less intuitive but TC: O(N) and SC: O(1)

        // Maintain a min and max
        // We would be checking the range of values count can take based on the sequence
        // We need to try that the ranges have no negatives as paranthesis count should not be negative as discussed in the dp appraoch
        // When we encounter a ( then range becomes mini+1, maxi+1
        // For a ) mini-1, maxi-1
        // For an *, We can take any value between [-1, 1] on mini and on maxi, in result mini -1 would be the most minimum so take that and in result maxi + 1would be the most maximum so take that
        // During traversal we also do that if mini goes negative reset it back to 0, then yes its a valid paranthesis otherwise not; this is the case when we are trying to take * as a closing bracket when already count is 0, so we are basically discarding that case by doing this
        // Also how would we differentiate if actually there was a closing bracket, mini would be -1, but maxi also would be -1, so we check during traversla if ever maxi goes below 0, if yes, we straight away return false
        // at last return mini==0;
        // EPIC

        // I. )))***
        // mini -1, maxi -1 (return false)


        // II. ()*)*()
        // 1. mini = 1, maxi = 1
        // 2. mini = 0, maxi = 0
        // 3. for asterisk, mini could have added -1,0,1; for -1 mini = -1, for 0 mini = 0, for 1, mini = 1; so most minimum and positive is 0, so we take -1, but if mini < 0, we reset to 0; and maxi will be +1 only among -1,0,1; thats why mini-1 and maxi+1 for *---------> mini = 0, maxi = 1
        // 4. mini = -1 -> 0, maxi = 0
        // 5. mini = -1 -> 0, maxi = 1
        // 6. mini = 1, maxi = 2
        // 7. mini = 0, maxi = 1

        // so mini == 0, above string is valid

        int mini = 0, maxi = 0;

        for(auto i: s) {
            if(i == '(') {
                mini++;
                maxi++;
            } else if(i == ')') {
                mini--;
                maxi--;
            } else {
                mini--;
                maxi++;
            }

            if(mini < 0) mini = 0;
            if(maxi < 0) return false;
        }
        return mini == 0;


    }

};
```

- Equivalent DP Approach: https://leetcode.com/problems/valid-parenthesis-string/submissions/2161905454/
