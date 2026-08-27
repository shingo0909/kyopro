// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/hash_vectorint.cpp
#include <bits/stdc++.h>
using namespace std;

struct hash_vector {
  public:
    vector<long long> hash;
    vector<long long> b;
    const long long mod = 838417471;
    const long long x = 89561;
    int n;
    hash_vector(vector<int> vec) : hash(vec.size() + 1, 0), b(vec.size() + 1, 1) {
        n = vec.size();
        for (int i = 1; i <= n; i++) {
            b[i] = b[i - 1] * x;
            b[i] %= mod;
        }
        hash[1] = vec[0];
        for (int i = 1; i <= n; i++) {
            hash[i] = hash[i - 1] * x + vec[i - 1];
            hash[i] %= mod;
        }
    }
    long long get_hash(int i, int j) {
        long long ans = hash[j + 1] - b[j - i + 1] * hash[i];
        return ((ans % mod) + mod) % mod;
    }
};