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
