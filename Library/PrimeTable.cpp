// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/PrimeTable.cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct PrimeTable {
  private:
    int n;
    vector<int> spf;
    vector<int> primes;
    vector<int> phi_table;
    vector<int> mu_table;

    void build() {
        spf[0] = -1;
        spf[1] = -1;
        phi_table[1] = 1;
        mu_table[1] = 1;

        for (int i = 2; i <= n; i++) {
            if (spf[i] == 0) {
                spf[i] = i;
                primes.push_back(i);
                phi_table[i] = i - 1;
                mu_table[i] = -1;
            }
            for (int p : primes) {
                if (p > spf[i] || 1LL * p * i > n)
                    break;
                spf[p * i] = p;
                if (p == spf[i]) {
                    phi_table[p * i] = phi_table[i] * p;
                    mu_table[p * i] = 0;
                } else {
                    phi_table[p * i] = phi_table[i] * (p - 1);
                    mu_table[p * i] = -mu_table[i];
                }
            }
        }
        return;
    }

  public:
    PrimeTable(int n) : n(n),
                        spf(n + 1, 0),
                        phi_table(n + 1, 0),
                        mu_table(n + 1, 0) {
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

    // オイラーのトーシェント関数 φ(x)
    long long phi(int x) const {
        return phi_table[x];
    }
    // メビウス関数 μ(x)
    int mu(int x) const {
        return mu_table[x];
    }
};