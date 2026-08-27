// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/SternBrocotTree.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Fraction {
    ll p, q;
    bool operator<(const Fraction &b) {
        return (__int128_t)p * b.q < (__int128_t)q * b.p;
    }
    bool operator>(const Fraction &b) {
        return (__int128_t)p * b.q > (__int128_t)q * b.p;
    }
    bool operator==(const Fraction &b) {
        return (__int128_t)p * b.q == (__int128_t)q * b.p;
    }
    bool operator<=(const Fraction &b) {
        return *this < b || *this == b;
    }
    bool operator>=(const Fraction &b) {
        return *this > b || *this == b;
    }
};

struct SternBrocotTree {
    Fraction L{0, 1};
    Fraction R{1, 0}; // infinity

    Fraction mid() const {
        return {L.p + R.p, L.q + R.q};
    }

    // 左にk回降りる
    void go_L(ll k) {
        R.p += k * L.p;
        R.q += k * L.q;
    }

    // 右にk回降りる
    void go_R(ll k) {
        L.p += k * R.p;
        L.q += k * R.q;
    }

    // (L.p + k*R.p)/(L.q + k*R.q) < target
    // となる最大のkを求める。
    ll max_R(const Fraction &t) {
        __int128_t num = (__int128_t)t.p * L.q - (__int128_t)L.p * t.q;
        __int128_t den = (__int128_t)R.p * t.q - (__int128_t)t.p * R.q;
        if (den <= 0 || num <= 0)
            return 0;
        return max(0LL, ll((num - 1) / den));
    }

    // (k*L.p + R.p)/(k*L.q + R.q) > target
    // となる最大のkを求める。
    ll max_L(const Fraction &t) const {
        __int128_t num = (__int128_t)R.p * t.q - (__int128_t)t.p * R.q;
        __int128_t den = (__int128_t)t.p * L.q - (__int128_t)L.p * t.q;
        if (den <= 0 || num <= 0)
            return 0;
        return max(0LL, ll((num - 1) / den));
    }
};

vector<ll> encode_path(Fraction x) {
    vector<ll> a;
    if (x.p < x.q) {
        a.push_back(0);
        swap(x.p, x.q);
    }
    while (x.p != 1) {
        a.push_back(x.p / x.q);
        x.p %= x.q;
        swap(x.p, x.q);
    }
    if (!a.empty()) {
        if (a.back() == 1)
            a.pop_back();
        else
            a.back()--;
    }
    return a;
}

SternBrocotTree decode_path(vector<ll> a) {
    SternBrocotTree sbt;
    for (int i = 0; i < (int)a.size(); i++) {
        if (i % 2)
            sbt.go_R(a[i]);
        else
            sbt.go_L(a[i]);
    }
    return sbt;
}

SternBrocotTree lca(Fraction &x, Fraction &y) {
    vector<ll> a = encode_path(x), b = encode_path(y);
    int n = min(a.size(), b.size());
    SternBrocotTree sbt;
    for (int i = 0; i < (int)n; i++) {
        if (i % 2)
            sbt.go_R(min(a[i], b[i]));
        else
            sbt.go_L(min(a[i], b[i]));
        if (a[i] != b[i])
            break;
    }
    return sbt;
}

SternBrocotTree range(Fraction x) {
    return decode_path(encode_path(x));
}
