//
// Created by zhouyxuiang on 2026/3/13.
//
#include <iostream>
#include <vector>
using namespace std;
//试除法(判断单个数字是否为素数)
bool isPrime(int x) {
    if (x <= 1) return false;
    if (x == 2) return true;
    for (int i = 2; i * i <= x; i ++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}
//2.埃氏筛(求很多素数)
//例如判断 2 ~ n之间所有的素数
//时间复杂度O(n log log n)
vector<bool> sieve(int n){
    //1.先假设所有数字都是素数
    vector<bool> isPrime(n + 1, true);
    //2.0 和 1 不是素数
    isPrime[0] = isPrime[1] = false;
    //3.从2开始筛选
    for (int i = 2; i * i <= n; i ++) {
        if (isPrime[i]) {
            //把i的倍数标记为合数
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}
int countPrimes(int n) {
    auto primes = sieve(n);
    int count = 0;
    for (int i = 2; i <= n; i ++) {
        if (primes[i]) count++;
    }
    return count;
}
//线性筛选素数
vector<int> Linear_sieve(int n) {
    vector<bool> isPrime(n + 1 , true);
    vector<int> primes;
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
        for (int j = 0 ; j < primes.size() ; j++) {
            int p = primes[j];
            if (i * p > n) {
                break;
            }
            isPrime[p * i] = false;
            if (i % p == 0) break;
        }
    }
    return primes;
}
int main() {
    cout << isPrime(10) << endl;
    cout << isPrime(2) << endl;
    //埃氏筛的应用
    //求素数的个数
    cout << countPrimes(1000000) << endl;
    vector<int> v = Linear_sieve(100);
    for_each(v.begin(), v.end(), [](int x) { cout << x << " "; } );
    return 0;
}