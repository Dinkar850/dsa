### June 30th

## Allocate books problem - GFG:

- bS on answers, standard problem

## Split array largest sum - LC:

- same solution as allocate books problem

## Max min height -> GFG practice

- Lambda functions: `[capture](parameters){body}`;
- line sweep + BS + Prefix Sum
- for a given height, check if flowers can reach to that height in the given number of days, if yes search for larger height otherwise search for lower height
- so in heights do a BS, with range = min_height to min_height + k + 1 (max height it can reach)

```cpp
auto fun = [&](int ht) {
    //ht is the height for which we need to check if flowers can reach this height in days
    int days = 0;
    int cht = arr[0]; //cht is current height of the flower, the height + height it has grown more due to increase in the whole subarray of length w;
    int diff = max(0, ht - cht); //0 if the flower's current height is greater than the ht we want it to reach, 0 days needed;
    days += diff;

    vector<int>flower(n + 1); //for storing difference in heights
    flower[0] += diff;
    flower[w] -= diff; //line sweep algo implementation

    //all above was initialization

    for(int i = 1; i < n; i++) {
        flower[i] += flower[i - 1]; //add to previous height
        int cht = a[i] + flower[i]; //original + height due to watering other plants
        int diff = max(0, ht - cht);
        days += diff;
        flowers[i] += diff;
        if(i + w < n) flowers[i + w] -= diff;
    }
    return days <= k;

}

//normal BS then on mid as ht, if !fun(mid) means days > k, h = m - 1; otherwise l = h + 1, return l -1 as answer and do this until l <= h
```
