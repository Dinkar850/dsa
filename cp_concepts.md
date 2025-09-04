## 30th June

## Binary exponentiation and Modular exponentiation

- calculating expo in log(expo) time
- idea: eg. 2 \*_ 13, (13)base2 = 1101, so 2 to the power (13) = 2 to the power (8 + 4 + 1) = 2 power 8 _ 2 power 4 \* 2 power 1 which is in total 13log2 operations of multiplication needed.
- so:

```cpp
fun(base, expo)
ll res = 1;
while(expo > 0) {
    if(exp & 1) res = res * base;
    base *= base;
    expo /= 2;
}
return res;
```

- in modular apply mod everywhere
- useful in calculations of exponentials in log time, or of large exponents.

## 17th July

## Euclidean algo for finding gcd

- gcd(a, b) = gcd(a - b, b) or gcd(b, a - b) in a recursive call, depends whether a - b is greater or b, and always in a recursive call we have a > b
- example: gcd(20, 15) = gcd(5, 15) -> gcd(15, 5) = gcd(10, 5) = gcd(5, 5) = gcd(0, 5) -> gcd(5, 0) and when b == 0, return a as the gcd.

```cpp
int gcd(a, b) {
    if(!b) return a;
    return (a - b >= b) ? gcd(a - b, b) : gcd(b, a - b);
}
```

## Power(x, n) or power exponentiation:

- one is binary and modular exponentiation which is written above and works in log(n) time
- this one also works somewhat in log2(n) time only
- works wonders for higher n
- idea is: if power is odd, multiply base to answer and make reduce power by 1 that makes it even, now if power is even dont do anything in ans just divide the power by 2 for the new power and square the base
- why because a to power 2n = a square to the power n
- this way we just have log(n) multiplication instead of n multiplications
- eg. , init ans as 1, power(3, 13) = ans _= 3, => power(3, 12) => power(9, 6) => power(81, 3) -> ans _= 81 => power(81, 2) => power(81 squared, 1) => ans \*= 81
- if seen its somewhat similar to binary exponentiation

```cpp
int power(int x, int n) {
    if(n == 0) return 1;
    if(n & 1) return x * power(x, n - 1);
    return power(x * x, n / 2);
}
```

- if power is negative, do 1 / answer
- if base is decimal or double, then use double for answer and divide by 1.0 instead of 1, in case power is negative
- use iteration instead of recursion to save extra stack space

```cpp
int power(int x, int n) {
    int ans = 1;
    while(n) {
        if(n & 1) {
            ans *= x;
            n--;
        } else {
            x *= x;
            n /= 2;
        }

    }
}
```

## Printing all divisors or factors of a number:

- yk in square root time you can get all divisors where n % i == 0 and i runs till root n, then i and n / i are divisors, if i == n/i then only add one of them.

## Sieve of Eratosthenes:

- TC: $$O{(n * log(log(n)))}$$
- check primes in ${O(1)}$

- the idea is to create an array of true and false until the number and marking each index as true first, marking 0 and 1 as false, and all those false which are not primes. Then by using this array, we can check for prime or not in O(1) time.
- so the algo is, you start from the index that is marked true and you mark all its multiples as false. multiples start from 1 + i of course, but starting from here, we observe that before i squared index, all would have been marked by its previous indices so we can safely start from i squared to n for marking multiples as false. Here's the algo:
- also as we are starting multiples from i squared, just end the loop when i squared is greater than n, so we loop from i = 2 to root of n only

```cpp
//let n be the number till where we wanna construct sieve
vector<int> primes(n + 1, true);
primes[0] = primes[1] = false;
for(int i = 2; i * i <= n; i++) {
    if(primes[i]) {
        for(int j = i * i; j <= n; j += i) primes[j] = false;
    }
}
//primes is your tool
```

- using this you can do a bunch of tasks:
  - check for any prime number in O(1) time, which otherwise would have taken O(root n). for single go for root n approach, for multiple go for sieve
  - calculate prime factors of a number in O(root n) by **large prime optimization** or also in O(logn) time by **pre-computation in sieve**.
  - check for LCMs, and anything related to divisors like checking if there are exactly 9 divisors of a number, or the largest power of some number k in n!

## Prime factors of a number

### First using Large Prime Optimization:

- the idea is to go from 2 to root n, check if the number is divisible by i and prime too, if yes then divide the number as many times as possible until (n % i == 0, and keep doing n /= i).
- do all this till root n, if still n is not 1 then it means n was eventually a prime number greater than root n. so at last we check if (n != 1), then add n as a factor too.

```cpp
vector<int> factors;
for(int i = 2; i * i <= n; i++) {
    if(checkPrime[i]) {
        if(n % i == 0) {
            while(n % i == 0) {
                n /= i;
            }
            factors.push_back(i);
        }

    }
}
if(n != 1) factors.push_back(n);
```

- this `checkPrime` is O(1) in sieve and O(root n) in normal prime check, so if you use sieve then only the algo is root n. This finds unique prime factors.
- if you start pushing back inside the while condition you get the actual prime factorization in O(root n) time after sieve creation in O(n \* log(logn)) time.

### Second using pre-computation in sieve:

- the idea is that while creating sieve, we can store the **smallest prime factor (SPF)** and use this information for calculating prime factorization of a number in O(logn) time. We use the same sieve algo but instead of marking all the multiples as false, we mark them as the SPF of the number

```cpp
vector<int> spf(n + 1);
//initialy mark each index as itself
for(int i = 0; i <= n; i++) spf[i] = i;
// now start marking spf:

for(int i = 2; i * i <= n; i++) {
    if(spf[i] == i) {
        for(int j = i * i; j <= n; j += i) spf[j] = min(spf[j], i);
    }
}
```

- then do the prime factorization of the number in O(logn) time by dividing the number till it n reaches 1 and pushing back the spf of the number in the vector.

```cpp

vector<int> primeFactorization;
while(n != 1) {
    primeFactorization.push_back(spf[n]);
    n /= spf[n];
}
```

- this is more efficient than the first approach, as it uses pre-computation of SPF, and also it is O(logn) time.

## 27th July

## Mobius Function:

Theres a lot so I'd suggest you to watch these videos:

- https://youtu.be/51RQaeEiVvQ?si=G0-zgGs8kp6RPAWw - explanation of mobius and usecases
- https://youtu.be/2H65yrmM0wY?si=LSpao9dFuZ4QlYR - counting coprimes
- https://youtu.be/k-hhka9LraI?si=iLJpjN38iDOPG7a7 - counting coprimes
