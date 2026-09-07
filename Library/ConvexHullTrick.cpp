#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct ConvexHullTrick {
    static const ll INF = LLONG_MAX;
    struct Line {
        mutable ll k, m, p;
        bool operator<(const Line &o) const { return k < o.k; }
        bool operator<(ll x) const { return p < x; }
    };

    multiset<Line, less<>> lines;

    static ll floordiv(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b != 0);
    }

    bool isect(multiset<Line, less<>>::iterator x,
               multiset<Line, less<>>::iterator y) {
        if (y == lines.end()) {
            x->p = INF;
            return false;
        }
        if (x->k == y->k) {
            x->p = (x->m > y->m) ? INF : -INF;
        } else {
            x->p = floordiv(y->m - x->m, x->k - y->k);
        }
        return x->p >= y->p;
    }

    // 直線 y = k*x + m を追加する
    void add(ll k, ll m) {
        auto z = lines.insert({k, m, 0});
        auto y = z++;
        auto x = y;

        while (isect(y, z)) {
            z = lines.erase(z);
        }

        if (x != lines.begin() && isect(--x, y)) {
            y = lines.erase(y);
            isect(x, y);
        }

        while ((y = x) != lines.begin() && (--x)->p >= y->p) {
            isect(x, lines.erase(y));
        }
    }

    // x における最大値を返す
    ll query(ll x) const {
        assert(!lines.empty());
        auto it = lines.lower_bound(x);
        return it->k * x + it->m;
    }

    bool empty() const { return lines.empty(); }
    size_t size() const { return lines.size(); }
};