// https://github.com/shingo0909/kyopro/blob/8144c73a9af5f00de991450b22a6e71867a50ede/Library/SlopeTrick.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SlopeTrick {
  private:
    static constexpr ll INF = 1LL << 61;

    ll min_f;
    priority_queue<ll, vector<ll>, less<ll>> L;
    priority_queue<ll, vector<ll>, greater<ll>> R;
    ll add_l, add_r;

    ll top_L() const { return L.empty() ? -INF : L.top() + add_l; }
    ll top_R() const { return R.empty() ? INF : R.top() + add_r; }

    void push_L(ll x) { L.push(x - add_l); }
    void push_R(ll x) { R.push(x - add_r); }

    ll pop_L() {
        ll x = top_L();
        L.pop();
        return x;
    }
    ll pop_R() {
        ll x = top_R();
        R.pop();
        return x;
    }

  public:
    SlopeTrick() : min_f(0), add_l(0), add_r(0) {}

    size_t size() const { return L.size() + R.size(); }

    // f(x) += a
    void add_all(ll a) {
        min_f += a;
    }

    // f(x) += max(x - a, 0)
    void add_x_minus_a(ll a) {
        if (top_L() <= a) {
            push_R(a);
        } else {
            min_f += top_L() - a;
            ll tmp = pop_L();
            push_L(a);
            push_R(tmp);
        }
    }

    // f(x) += max(a - x, 0)
    void add_a_minus_x(ll a) {
        if (top_R() >= a) {
            push_L(a);
        } else {
            min_f += a - top_R();
            ll tmp = pop_R();
            push_R(a);
            push_L(tmp);
        }
    }

    // f(x) += |x - a|
    void add_abs(ll a) {
        add_x_minus_a(a);
        add_a_minus_x(a);
    }

    // 最小値
    ll get_min() const {
        return min_f;
    }

    // 最小値をとる x の範囲 [l, r] (l == r なら一点で最小)
    pair<ll, ll> get_argmin() const {
        return {top_L(), top_R()};
    }
};
