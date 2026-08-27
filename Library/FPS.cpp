// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/FPS.cpp
#include <atcoder/convolution>
#include <atcoder/modint>
#include <bits/stdc++.h>

using namespace std;
using namespace atcoder;
using mint = modint998244353;
using ll = long long;

struct FPS : vector<mint> {
    using vector<mint>::vector;

    // 正規化
    void normalize() {
        while (!this->empty() && this->back() == 0)
            this->pop_back();
        return;
    }

    // vector<mint>からの代入
    FPS &operator=(const vector<mint> &v) {
        vector<mint>::operator=(v);
        return *this;
    }

    // 切り出し
    FPS get(int l, int r) const {
        assert(0 <= l && l <= r);
        return FPS(begin() + min(l, (int)this->size()), begin() + min(r, (int)this->size()));
    }
    FPS get(int r) const {
        return get(0, r);
    }

    FPS rev() const {
        return FPS(rbegin(), rend());
    }

    // 加算
    FPS &operator+=(const FPS &r) {
        if (r.size() > this->size())
            this->resize(r.size());
        for (int i = 0; i < int(r.size()); i++)
            (*this)[i] += r[i];
        normalize();
        return *this;
    }

    // 減算
    FPS &operator-=(const FPS &r) {
        if (r.size() > this->size())
            this->resize(r.size());
        for (int i = 0; i < int(r.size()); i++)
            (*this)[i] -= r[i];
        normalize();
        return *this;
    }

    // スカラー倍
    FPS &operator*=(const mint &c) {
        for (auto &x : *this)
            x *= c;
        return *this;
    }

    // スカラー除算
    FPS &operator/=(const mint &c) {
        mint inv_c = c.inv();
        for (auto &x : *this)
            x *= inv_c;
        return *this;
    }

    // 積
    FPS &operator*=(const FPS &r) {
        *this = convolution(*this, r);
        return *this;
    }

    // 除算
    FPS &operator/=(const FPS &r) {
        assert(!r.empty());
        assert(r.back() != 0);
        normalize();
        int deg = int(size()) - int(r.size()) + 1;
        if (deg <= 0) {
            clear();
            return *this;
        }
        *this = ((*this).rev().get(deg) * r.rev().inv(deg)).get(deg).rev();
        return *this;
    }

    // 剰余
    FPS &operator%=(const FPS &r) {
        assert(!r.empty());
        assert(r.back() != 0);
        normalize();
        FPS q = (*this) / r;
        return *this -= q * r;
    }

    friend FPS operator+(FPS l, const FPS &r) { return l += r; }
    friend FPS operator-(FPS l, const FPS &r) { return l -= r; }
    friend FPS operator*(FPS l, const FPS &r) { return l *= r; }
    friend FPS operator*(FPS l, const mint &r) { return l *= r; }
    friend FPS operator/(FPS l, const FPS &r) { return l /= r; }
    friend FPS operator/(FPS l, const mint &r) { return l /= r; }
    friend FPS operator%(FPS l, const FPS &r) { return l %= r; }

    // 逆元
    FPS inv(const int &n) const {
        assert((*this)[0] != 0);
        FPS res({mint(1) / (*this)[0]});
        int m = 1;
        while (m < n) {
            m <<= 1;
            res = (res * 2 - (res * res * (*this).get(m)).get(m)).get(m);
        }
        res.resize(n);
        return res;
    }

    // 微分
    FPS diff() const {
        if (empty())
            return FPS();
        int n = size();
        FPS res(n - 1);
        for (int i = 1; i < n; i++)
            res[i - 1] = (*this)[i] * i;
        return res;
    }

    // 積分
    FPS integral() const {
        int n = size();
        FPS res(n + 1, 0);
        for (int i = 0; i < n; i++)
            res[i + 1] = (*this)[i] / (i + 1);
        return res;
    }

    // log
    FPS log(const int &n) const {
        assert((*this)[0] == 1);
        FPS res = (diff() * inv(n)).integral();
        res.resize(n);
        return res;
    }

    // exp
    FPS exp(const int &n) const {
        assert((*this)[0] == 0);
        FPS res(1, 1);
        int m = 1;
        while (m < n) {
            m <<= 1;
            res = res * (get(m) - res.log(m) + FPS(1, 1)).get(m);
        }
        res.resize(n);
        return res;
    }

    // pow
    FPS pow(const ll &p, const int &n) const {
        if (p == 0) {
            FPS res(n);
            res[0] = 1;
            return res;
        }
        ll i = 0;
        int m = size();
        while (i < m && (*this)[i] == 0)
            i++;
        if (i == m)
            return FPS(n);
        if (__int128_t(i) * p >= n)
            return FPS(n);
        mint c = (*this)[i];
        FPS g = ((get(i, m) / c).log(n) * p).exp(n) * c.pow(p);
        FPS res(i * p);
        for (auto &x : g)
            res.push_back(x);
        res.resize(n);
        return res;
    }
};

// BostanMori法
// p/qの第n項を求める。
mint BostanMori(FPS p, FPS q, ll n) {
    if (n == 0)
        return p[0] / q[0];
    int qsize = q.size();
    FPS mq = q;
    for (int i = 1; i < q.size(); i += 2)
        mq[i] *= -1;
    FPS p2 = p * mq;
    FPS q2 = q * mq;
    p2.resize(2 * qsize);
    q2.resize(2 * qsize);
    FPS s(qsize);
    FPS t(qsize);
    for (int i = 0; i < qsize; i++) {
        s[i] = (n % 2 ? p2[2 * i + 1] : p2[2 * i]);
        t[i] = q2[2 * i];
    }
    return BostanMori(s, t, n >> 1);
}
