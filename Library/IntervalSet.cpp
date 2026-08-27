// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/IntervalSet.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct IntervalSet {
  private:
    const ll INF = 1LL << 62;
    set<pair<ll, ll>> s;
    ll siz;

    ll len(ll l, ll r) { return r - l; }
    void insert_interval(ll l, ll r) {
        s.insert({l, r});
        siz += len(l, r);
        return;
    }
    auto erase_interval(set<pair<ll, ll>>::iterator it) {
        siz -= len(it->first, it->second);
        return s.erase(it);
    }

  public:
    IntervalSet() : siz(0) {
        s.insert({-INF, -INF});
        s.insert({INF, INF});
    }

    auto get(ll x) const {
        auto it = prev(s.upper_bound({x, LLONG_MAX}));
        if (it->first <= x && x < it->second)
            return it;
        return s.end();
    }

    void add(ll l, ll r) {
        if (l >= r)
            return;
        auto it = prev(s.lower_bound({l, -1}));
        if (it->second < l)
            it++;

        while (it->first <= r) {
            l = min(l, it->first);
            r = max(r, it->second);
            it = erase_interval(it);
        }
        insert_interval(l, r);
        return;
    }
    void remove(ll l, ll r) {
        if (l >= r)
            return;
        auto it = prev(s.upper_bound({l, INF}));
        if (it->second <= l)
            ++it;

        vector<pair<ll, ll>> add;

        while (it->first < r) {
            ll L = it->first, R = it->second;
            it = erase_interval(it);

            if (L < l)
                add.push_back({L, l});
            if (r < R)
                add.push_back({r, R});
        }

        for (auto &p : add)
            insert_interval(p.first, p.second);
    }

    bool contains(ll x) {
        auto it = prev(s.upper_bound({x, INF}));
        return it->first <= x && x < it->second;
    }

    ll size() const {
        return siz;
    }
};