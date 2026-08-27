// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/Combination.cpp
#include <atcoder/modint>
#include <bits/stdc++.h>

using namespace std;
using mint = atcoder::modint998244353;

struct Combination {
    vector<mint> fact, fact_inv;
    Combination() {
        fact = {1};
        fact_inv = {1};
    }
    void ensure(int n) {
        int cur = fact.size() - 1;
        if (cur >= n)
            return;
        n *= 1.1;
        fact.resize(n + 1);
        fact_inv.resize(n + 1);
        for (int i = cur + 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i;
        }
        fact_inv[n] = fact[n].inv();
        for (int i = n; i > cur; i--) {
            fact_inv[i - 1] = fact_inv[i] * i;
        }
        return;
    }
    mint C(int a, int b) {
        if (b < 0 || b > a)
            return 0;
        ensure(a);
        return fact[a] * fact_inv[b] * fact_inv[a - b];
    }
    mint F(int a) {
        ensure(a);
        return fact[a];
    }
    mint Finv(int a) {
        ensure(a);
        return fact_inv[a];
    }
};