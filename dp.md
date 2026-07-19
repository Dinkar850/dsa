## 8th July:

## 1751. Maximum Number of Events That Can Be Attended II

- dp + bs
- the issue was not wanting to store day as a third parameter in dp array
- not wanting coz it could increase time complexity a lot for a huge amount of day
- but if dont store day, then dp[i][k] would give wrong answer for different days as its same for different days
- if its set for some day 1, then for day 2 it will be same. That is what is conventional dp, any changing parameter needs its own dimension
- so in place of storing day we jump to the next valid index using a classic optimization of binary search to find the next valid index

- If you use the day parameter and always move to i+1, you must include day in your DP state, which is infeasible for large ranges.
- By jumping directly to the next valid event (whose start day is after the current event’s end day), you eliminate the need to track day in your DP state. This is because, for each i and k, the state is now unique and independent of the path taken to reach it.
  <br>

**This is a classic optimization in interval scheduling/DP problems:**

- Binary search (or linear scan) for the next eligible event lets you use a much smaller DP table (dp[i][k]), making the solution efficient and practical.
  <br>

**Summary:**

- Tracking day in DP is only needed if your recursion can revisit the same event index with different "current days."
- If you always jump to the next eligible event, you don’t need to track day in DP.
  This trick is very common in problems involving intervals, events, or jobs with start/end times!
  <br>

**For even better optimization, you can precompute the next valid index for each event using binary search and use it in the problem to compute next index in O(1) time, reducing the overall complexity to O(nk) instead of O(nklogn).**
<br>

**Similar questions:**

- Weighted Job Scheduling:
  https://www.geeksforgeeks.org/problems/weighted-job-scheduling/1

## 16th July

## DP + Bitmasking

- when there are a lot of dimensions needed to represent a dp state, bitmasking helps us to identify the state uniquely
- dp[i][state] can be defined uniquely
- state is the bitmask of picking or not picking where picking = 1, non picking = 0
- using bit operations and manipulations one can find out the state, or value
- its often used when you are stuck with how to uniquely identify for more than one answer at an index i depending upon the picks and non picks of previoius state
- its useful when these picks and non picks have to be done at the length which can be fit in the mask, usually less than 30 to be able to represent the state in integer only
- see questions: `number of ways to assign hats`, `number of ways to paint grid of n x 3`, `painting grid with 3 colors` and `earliest and latest meetings` (this problem also uses the concept of geometry for unique state identification where the number of active meetings before left, after right and between left and right uniqeuly identifies the state of the array)

## 20th July (but in 2026, above was 2025)

## Crazy problem on successive optimizations

- Link: https://www.geeksforgeeks.org/problems/cut-matrix/1

### First optimization: Normal Memoization + Suffix 2D Sum

- TC is O(n _ m _ (n + m)) which exceeds 1s

```cpp
class Solution {
    const int mod = 1e9 + 7;
  public:
    int solve(int r, int c, int k, vector<vector<int>> &suff, vector<vector<vector<int>>>& dp, vector<vector<int>>& matrix) {
        if (k == 1) return suff[r][c] >= 1; //when only 1 cut remains and below matrix has no 1s, return 0 otherwise 1 for a valid cut
        if(dp[r][c][k] != -1) return dp[r][c][k];

        long long ans = 0;
        int n = matrix.size();
        int m = matrix[0].size();

        //attempting horizontal cut
        for(int i = r + 1; i < n; i++) {
            if(suff[i][c] == suff[r][c]) continue; //skip when next row has same 1s as it would mean that above row has no 1s (then only previous and next rows are same), so in that case a cut would not be valid
            ans = (ans + solve(i, c, k - 1, suff, dp, matrix)) % mod;
        }

        //attempting vertical cut
        for(int i = c + 1; i < m; i++) {
            if(suff[r][i] == suff[r][c]) continue; // same logic as in rows
            ans = (ans + solve(r, i, k - 1, suff, dp, matrix)) % mod;
        }

        return dp[r][c][k] = ans;
    }

    int findWays(vector<vector<int>>& matrix, int k) {
        // code here
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(k + 1, -1)));
        vector<vector<int>> suff(n + 1, vector<int>(m + 1, 0));

        //building suffix matrix
        for(int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                suff[i][j] = matrix[i][j] + suff[i + 1][j] + suff[i][j + 1] - suff[i + 1][j + 1];
            }
        }

        return solve(0, 0, k, suff, dp, matrix);
    }
};
```

### 2nd optimization

- We see that the loops for calculating next row and next column could be optimized
- We are skipping the rows with same values, and same with cols
- Can we build someething that precomputes the next valid index we should jump to for both rows and columns
- We observe that we need to find the next index such that the number of 1s at the index is lesser than that of the comparison index

```cpp
//for rows, initially build a matrix say next_row that gives us the next index we should directly jump to for each column
// same for cols
// rest of the optimzation logic is mentioned here:

class Solution {
    const int mod = 1e9 + 7;
  public:
    int solve(int r, int c, int k, vector<vector<int>> &suff, vector<vector<vector<int>>>& dp, vector<vector<vector<int>>>& dp_row_sum, vector<vector<vector<int>>>& dp_col_sum, vector<vector<int>>& matrix, vector<vector<int>>& next_row, vector<vector<int>>& next_col) {
        if (k == 1) return suff[r][c] >= 1;
        if(dp[r][c][k] != -1) return dp[r][c][k];

        long long ans = 0;
        int n = matrix.size();
        int m = matrix[0].size();

        // now we can instantly go to the next row and next col using those matrices we built,
        // but the catch is that we need to completely remove the need of a loop.
        // An observation is that if we find a valid index at say r, then
        // r + 1, r + 2, r + 3 etc will also be valid and we wont need to compute those using loop, if
        // we have them precomputed using another function.
        // Basically we want to save these computations using loop, if we are at r then
        // we are doing solve(r + 1) + solve(r + 2) + solve(r + 3)....
        // For solve(r + 1) we are doing again solve(r + 2) + solve (r + 3)
        // But what if we already had solve(r + 2) + solve(r + 3), we cud have simply done,
        // ans + some_func(next_row[r][c]), where r is next_row[r][c] (next valid index, here above, r = 2)
        // some_func for last index is solve(r)
        // for r - 1 is solve(r - 1) + solve(r) and so on, and so this cud also be precomputed using a dp_sum matrix
        // for r - 2 is solve(r - 2) + solve(r - 1) + solve(r) = solve(r - 2) + some_func(r - 1)
        // store some_func(r - 1) in a dp array

        // //attempting horizontal cut

        // for(int i = r + 1; i < n; i++) {
        //     if(suff[i][c] == suff[r][c]) continue; // now calculated by next_row
        //     ans = (ans + solve(i, c, k - 1, suff, dp, matrix)) % mod; //now calculted by row_sum
        // }

        // in place of above loop now we can write:
        if(next_row[r][c] < n) ans = (ans + row_sum(next_row[r][c], c, k - 1, matrix, dp_row_sum, dp_col_sum, suff, dp, next_row, next_col)) % mod;

        // //attempting vertical cut
        // for(int i = c + 1; i < m; i++) {
        //     if(suff[r][i] == suff[r][c]) continue;
        //     ans = (ans + solve(r, i, k - 1, suff, dp, matrix)) % mod;
        // }

        // in place of above loop we can write:
        if(next_col[r][c] < m) ans = (ans + col_sum(r, next_col[r][c], k - 1, matrix, dp_row_sum, dp_col_sum, suff, dp, next_row, next_col)) % mod;


        return dp[r][c][k] = ans;
    }

    // equivalent to some_func
    int row_sum(int r, int c, int k, vector<vector<int>>& matrix, vector<vector<vector<int>>>& dp_row_sum, vector<vector<vector<int>>>& dp_col_sum, vector<vector<int>> &suff, vector<vector<vector<int>>>& dp, vector<vector<int>> &next_row, vector<vector<int>> &next_col) {
        int n = matrix.size();
        if (r == n) return 0; // 0 for the last row
        if(dp_row_sum[r][c][k] != -1) return dp_row_sum[r][c][k]; //already present in dp
        return dp_row_sum[r][c][k] = (solve(r, c, k, suff, dp, dp_row_sum, dp_col_sum, matrix, next_row, next_col) + row_sum(r + 1, c, k, matrix, dp_row_sum, dp_col_sum, suff, dp, next_row, next_col) ) % mod; //some_func(r - 2) = solve(r - 2) + some_func(r - 1)
    }

    int col_sum(int r, int c, int k, vector<vector<int>>& matrix, vector<vector<vector<int>>>& dp_row_sum, vector<vector<vector<int>>>& dp_col_sum, vector<vector<int>> &suff, vector<vector<vector<int>>>& dp, vector<vector<int>> &next_row, vector<vector<int>> &next_col) {
        int m = matrix[0].size();
        if (c == m) return 0; // 0 for the last col
        if(dp_col_sum[r][c][k] != -1) return dp_col_sum[r][c][k]; //already present in dp
        return dp_col_sum[r][c][k] = (solve(r, c, k, suff, dp, dp_row_sum, dp_col_sum, matrix, next_row, next_col) + col_sum(r, c + 1, k, matrix, dp_row_sum, dp_col_sum, suff, dp, next_row, next_col)) % mod;
    }

    int findWays(vector<vector<int>>& matrix, int k) {
        // code here
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(k + 1, -1)));
        vector<vector<vector<int>>> dp_row_sum(n + 1, vector<vector<int>>(m + 1, vector<int>(k + 1, -1)));
        vector<vector<vector<int>>> dp_col_sum(n + 1, vector<vector<int>>(m + 1, vector<int>(k + 1, -1)));
        vector<vector<int>> suff(n + 1, vector<int>(m + 1, 0)), next_row(n, vector<int>(m, 0)), next_col(n, vector<int>(m, 0));


        for(int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                suff[i][j] = matrix[i][j] + suff[i + 1][j] + suff[i][j + 1] - suff[i + 1][j + 1];
            }
        }

        //building next row matrix with following logic
        // store i = n in the last row for each col
        // go up and check if upper cell has greater number of 1s, we store i + 1 index that tells jump to the i + 1 index directly and row i is a valid cut

        for (int c = 0; c < m; c++) {
            next_row[n - 1][c] = n;
            for(int r = n - 2; r >= 0; r--) {
                if (suff[r + 1][c] == suff[r][c]) next_row[r][c] = next_row[r + 1][c];
                else next_row[r][c] = r + 1;
            }
        }

        // same for next_col
        for (int r = 0; r < n; r++) {
            next_col[r][m - 1] = m;
            for(int c = m - 2; c >= 0; c--) {
                if (suff[r][c + 1] == suff[r][c]) next_col[r][c] = next_col[r][c + 1];
                else next_col[r][c] = c + 1;
            }
        }

        return solve(0, 0, k, suff, dp, dp_row_sum, dp_col_sum, matrix, next_row, next_col);
    }
};
```
