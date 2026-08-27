// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/MillerRabin.cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll pow_mod(__int128_t a, __int128_t n, __int128_t m) {
    __int128_t res = 1;
    a %= m;
    while (n) {
        if (n % 2) {
            res *= a;
            res %= m;
        }
        a *= a;
        a %= m;
        n /= 2;
    }
    return res;
}

// ミラーラビン法
// 参考:https://drken1215.hatenablog.com/entry/2023/05/23/233000
bool MillerRabin(ll n) {
    if (n <= 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;

    const vector<ll> A = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    ll s = 0;
    ll d = n - 1;

    while (d % 2 == 0) {
        s++;
        d /= 2;
    }

    for (ll a : A) {
        if (a % n == 0)
            continue;
        ll x = pow_mod(a, d, n);
        if (x != 1) {
            bool ok = false;
            for (int i = 0; i < s; i++) {
                if (x == n - 1) {
                    ok = true;
                    break;
                }
                x = pow_mod(x, 2, n);
            }
            if (!ok)
                return false;
        }
    }
    return true;
}
