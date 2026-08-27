// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/ImplicitTreap.cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct ImplicitTreap {
  private:
    struct Node {
        ll val;
        ll pri;
        int sz;
        int l, r;
    };
    vector<Node> pool;
    int root = 0;
    mt19937 rng;

    int size() const { return pool[root].sz; }
    bool empty() const { return size() == 0; }

    int newNode(long long v) {
        pool.push_back(Node{v, (unsigned)rng(), 1, 0, 0});
        return (int)pool.size() - 1;
    }
    int sz(int t) const { return t ? pool[t].sz : 0; }

    void pull(int t) {
        if (!t)
            return;
        Node &n = pool[t];
        n.sz = 1 + sz(n.l) + sz(n.r);
        return;
    }

    void split(int t, int k, int &l, int &r) {
        if (!t) {
            l = r = 0;
            return;
        }
        if (sz(pool[t].l) < k) {
            l = t;
            split(pool[t].r, k - sz(pool[t].l) - 1, pool[t].r, r);
            pull(l);
        } else {
            r = t;
            split(pool[t].l, k, l, pool[t].l);
            pull(r);
        }
    }

    int merge(int l, int r) {
        if (!l || !r)
            return l ? l : r;
        if (pool[l].pri > pool[r].pri) {
            pool[l].r = merge(pool[l].r, r);
            pull(l);
            return l;
        } else {
            pool[r].l = merge(l, pool[r].l);
            pull(r);
            return r;
        }
    }

  public:
    ImplicitTreap(int reserve_n = 0) : rng(random_device{}()) {
        pool.reserve(reserve_n + 1);
        pool.push_back(Node{0, 0, 0, 0, 0});
    }
    // vのindexがposになるように挿入
    void insert(int pos, long long v) {
        int l, r;
        split(root, pos, l, r);
        root = merge(merge(l, newNode(v)), r);
    }
    // indexがposの要素を削除
    ll erase(int pos) {
        int l, mid, r;
        split(root, pos, l, mid);
        split(mid, 1, mid, r);
        long long v = pool[mid].val;
        root = merge(l, r);
        return v;
    }
    // indexがposの要素を取得
    ll at(int pos) {
        int l, mid, r;
        split(root, pos, l, mid);
        split(mid, 1, mid, r);
        long long v = pool[mid].val;
        root = merge(merge(l, mid), r);
        return v;
    }

    void push_back(ll v) { insert(size(), v); }
    void push_front(ll v) { insert(0, v); }
    ll pop_front() { return erase(0); }
    ll pop_back() { return erase(size() - 1); }
};
