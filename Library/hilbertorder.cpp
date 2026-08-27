// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/hilbertorder.cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 参考https://take44444.github.io/Algorithm-Book/range/mo/main.html
ll maxn = 1 << 30;
ll hilbertorder(int x, int y) {
    ll rx, ry, d = 0;
    for (ll s = maxn >> 1; s; s >>= 1) {
        rx = (x & s) > 0, ry = (y & s) > 0;
        d += s * s * ((rx * 3) ^ ry);
        if (ry)
            continue;
        if (rx) {
            x = maxn - 1 - x;
            y = maxn - 1 - y;
        }
        swap(x, y);
    }
    return d;
}