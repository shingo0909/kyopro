// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/PrimeTable.cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct PrimeTable {
  private:
    int n;
    vector<int> spf;
    vector<int> primes;
    void build() {
        spf[0] = -1;
        spf[1] = -1;

        for (int i = 2; i <= n; i++) {
            if (spf[i] == 0) {
                spf[i] = i;
                primes.push_back(i);
            }
            for (int p : primes) {
                if (p > spf[i] || 1LL * p * i > n)
                    break;
                spf[p * i] = p;
            }
        }
        return;
    }

  public:
    PrimeTable(int n) : n(n), spf(n + 1, 0) {
        build();
    }

    bool is_prime(int x) const {
        return x >= 2 && spf[x] == x;
    }

    // 素因数分解
    vector<pair<int, int>> factorize(int x) const {
        vector<pair<int, int>> res;
        while (x > 1) {
            int p = spf[x];
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }
            res.emplace_back(p, cnt);
        }
        return res;
    }

    // 約数列挙
    // ソートされていないことに注意
    vector<int> divisors(int n) const {
        vector<int> res{1};
        auto pf = factorize(n);
        for (auto p : pf) {
            int s = (int)res.size();
            for (int i = 0; i < s; i++) {
                int v = 1;
                for (int j = 0; j < p.second; j++) {
                    v *= p.first;
                    res.push_back(res[i] * v);
                }
            }
        }
        return res;
    }
};
