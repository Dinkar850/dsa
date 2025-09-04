## 30th June

## 1498. Number of Subsequences That Satisfy the Given Sum Condition

- calculating expo in log(expo) time (binary and modular exponentiation, altho cud have done it by precomputing powers of 2, where index = exponent)
- for mod and binary expo check <a href="/cp_concepts.md">Cp</a>
- another useful deduction is that number of subsequences from index i to j is 2 to the power (j - i);

## 2nd July

## 3333. Find the Original Typed String II

- mod of subtraction: (a - b + mod) % mod
- constructing strings with characters with given frequency array of each character and of length <= k using dp and prefix sum. `inv` is the total strings and `dp[i] = total strings of length i`
- prefix sum of dp array is being calculated

```cpp
//MAIN LOGIC STARTS:
        //now our goal is to find out the strings that can be formed by characters in segments vector(Treat each value as frequency)
        //those strings must have length <= k where new k = k - ml
        // that is if our goal was to find strings <= 9, our updated goal is to find strings of length 0 to 3 for the eg in aaabbbbccddbb, k = 9
        //that is we need to find extra characters that we can add in the min string of abcdb

        //the dp array is going to find number of possible strings of length index
        //that is dp[i] = possible strings of length i
        //at last to find all strings of length <= k - ml, add all the values of dp array, which will give us the invalid strings
        // see below code:


        //use of prefix array:
        //what we are doing is, lets say our segment array is [2, 3, 1, 1, 1], for chars: a, b, c, d, b
        // a is available 2 times, that means we can take a 0 times, 1 time or 2 times
        // and due to 'a' taking 0, 1 or 2 times, dp[i] = dp[i - 0] + dp[i - 1] + dp[i - 2] for 'a'
        //dp[i - 0] = taking 'a' 0 times, dp[i - 1] = taking 'a' 1 time, dp[i - 2] = taking 'a' 2 times
        //the prefix array calculates this sum in O(1) time.
        //prefix[i] = dp[0] + dp[1] + dp[2] + ..... + dp[i]
        //so dp[i] = pre[i] - pre[i - x - 1] for i - x - 1 >= 0 and pre[i] otherwise
        k -= ml;
        vector<ll> dp(k);
        dp[0] = 1;
        for(int x: seg) {
            vector<ll> pre(k);
            pre[0] = dp[0];
            for(int i = 1; i < k; i++) {
                pre[i] = (pre[i - 1] + dp[i]) % mod;
            }
            for(int i = 1; i < k; i++) {
                if(i - x - 1 >= 0) dp[i] = (pre[i] - pre[i - x - 1] + mod) % mod;
                else dp[i] = pre[i];
            }
        }
        int inv = 0;
        for(ll i: dp) {
            inv = (inv + i) % mod;
        }
```

## 3rd July and 4th July

## 3307. Find the K-th Character in String Game I and II

- a string is formed by using the previous string like this:
- 'a' to 'ab' to 'abbc' to 'abbcbccd' that is concatenating the previous string with each character of previoud string added by 1

## Number of subsequences and substrings or subarrays between two indices i and j

- between any two indices i and j, number of subsequences is equal to `2 to the power (j - i + 1) - 1`. evidently you will have to precompute powers of 2 for big indices
- between any two indices i and j, number of substrings is equal to `[(j - i + 2) * (j - i + 1)] / 2`. as you move the j pointer to right by fixing i pointer at some index, the number of substrings increases by (j - i + 1).
- example: in `abc`, i = 0 and j = 2, number of substrings will be ([3 * 4] / 2) which is 6
- but lets say initially i is at 0 and so is j, as you increase j by 1, substrings b and ab will be added so 2 are added, and as you increase j by 1 again, substring abc, bc, c are added so 3 are added, and so on..1 + 2 + 3 and so on.. , so increasing j adds up (j - i + 1) substrings. Subsequenlty if you increase i by 1, you will again be adding other substrings that meet the condition. (Look at `Subarrays With At Most K Distinct Integers (GFG)`)

## 16th July

## divisible by 13 (gfg)

- using concept of (a _ b + c) % m = (a % m _ b % m + c % m) % m
- here b was 10 so 10 % 13 = 10 was used always and c was a number between 0 and 9 so this was also used readily, while a that was num was always mod
- you can use this for any number divisibility check, for very long numbers given as strings

## 31st July

- Line Sweep technique for computing largest number that appears in at least k intervals. In a map, mp[start of interval]: +1, mp[end of interval + 1]: -1, then copy map pairs in a vector of pairs
- traverse in that vector of pairs to compute the prefix sum of second elements of pairs denoting the number of times a number betweeen two limits appears
- then if ps[i - 1].second >= k, store ps[i].first - 1 as the answer as we were doing mp[end + 1] as -1.
