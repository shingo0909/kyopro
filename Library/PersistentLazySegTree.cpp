#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <class S, S (*op)(S, S), S (*e)(),
          class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct PersistentLazySegTree {
    struct Node {
        int l, r;
        S val;
        F lazy;
        Node(int l, int r, S val, F lazy) : l(l), r(r), val(val), lazy(lazy) {}
    };
    int n;
    vector<Node> pool;
    vector<int> root;

  private:
    int new_node(const Node &v) {
        pool.push_back(v);
        return (int)pool.size() - 1;
    }

    int build(int l, int r) {
        if (l + 1 == r) {
            return new_node(Node(-1, -1, e(), id()));
        }

        int m = (l + r) / 2;
        int node_l = build(l, m);
        int node_r = build(m, r);

        return new_node(
            Node(node_l, node_r, op(pool[node_l].val, pool[node_r].val), id()));
    }

    int build_vec(int l, int r, vector<S> &vec) {
        if (l + 1 == r) {
            return new_node(Node(-1, -1, vec[l], id()));
        }

        int m = (l + r) / 2;
        int node_l = build_vec(l, m, vec);
        int node_r = build_vec(m, r, vec);

        return new_node(
            Node(node_l, node_r, op(pool[node_l].val, pool[node_r].val), id()));
    }

    int apply_node(int cur, F f) {
        Node nd = pool[cur];
        nd.val = mapping(f, nd.val);
        nd.lazy = composition(f, nd.lazy);
        return new_node(nd);
    }

    int push_down(int cur) {
        Node nd = pool[cur];
        if (nd.l == -1)
            return cur;
        F f = nd.lazy;

        nd.l = apply_node(nd.l, f);
        nd.r = apply_node(nd.r, f);
        nd.lazy = id();
        return new_node(nd);
    }

    int update(int cur, int l, int r, int pos, S x) {
        cur = push_down(cur);
        Node nd = pool[cur];
        if (l + 1 == r) {
            nd.val = x;
            nd.lazy = id();
            return new_node(nd);
        }
        int m = (l + r) / 2;
        if (pos < m)
            nd.l = update(nd.l, l, m, pos, x);
        else
            nd.r = update(nd.r, m, r, pos, x);
        nd.val = op(pool[nd.l].val, pool[nd.r].val);
        return new_node(nd);
    }

    int apply_range(int cur, int l, int r, int ql, int qr, F f) {
        if (qr <= l || r <= ql)
            return cur;
        if (ql <= l && r <= qr)
            return apply_node(cur, f);

        cur = push_down(cur);
        Node nd = pool[cur];
        int m = (l + r) / 2;
        nd.l = apply_range(nd.l, l, m, ql, qr, f);
        nd.r = apply_range(nd.r, m, r, ql, qr, f);
        nd.val = op(pool[nd.l].val, pool[nd.r].val);
        return new_node(nd);
    }

    S query(int cur, int l, int r, int ql, int qr, F accumulated) const {
        if (qr <= l || r <= ql)
            return e();
        if (ql <= l && r <= qr)
            return mapping(accumulated, pool[cur].val);

        F next = composition(accumulated, pool[cur].lazy);
        int m = (l + r) / 2;
        return op(query(pool[cur].l, l, m, ql, qr, next),
                  query(pool[cur].r, m, r, ql, qr, next));
    }

    // 区間コピー
    int copy_range(int cur_a, int cur_b, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql)
            return cur_a;
        if (ql <= l && r <= qr)
            return cur_b;

        cur_a = push_down(cur_a);
        cur_b = push_down(cur_b);

        Node na = pool[cur_a];
        Node nb = pool[cur_b];

        int m = (l + r) / 2;
        int new_l = copy_range(na.l, nb.l, l, m, ql, qr);
        int new_r = copy_range(na.r, nb.r, m, r, ql, qr);

        return new_node(Node(new_l, new_r, op(pool[new_l].val, pool[new_r].val), id()));
    }

  public:
    // 単位元e()で構築
    PersistentLazySegTree(int N) : n(N) { root.push_back(build(0, n)); }
    // 配列vector<S>から構築
    PersistentLazySegTree(vector<S> v) : n(v.size()) {
        root.push_back(build_vec(0, n, v));
    }

    // バージョン指定して区間更新
    int apply(int l, int r, F f, int ver) {
        int nr = apply_range(root[ver], 0, n, l, r, f);
        root.push_back(nr);
        return (int)root.size() - 1;
    }
    // 最新バージョンを区間更新
    int apply(int l, int r, F f) {
        return apply(l, r, f, (int)root.size() - 1);
    }

    // バージョン指定して更新
    int set(int pos, S x, int ver) {
        int new_root = update(root[ver], 0, n, pos, x);
        root.push_back(new_root);
        return (int)root.size() - 1;
    }
    // 最新バージョンを更新
    int set(int pos, S x) { return set(pos, x, (int)root.size() - 1); }

    // バージョン指定して取得
    S prod(int l, int r, int ver) const {
        return query(root[ver], 0, n, l, r, id());
    }
    S get(int i, int ver) const { return prod(i, i + 1, ver); }
    // 最新バージョンで取得
    S prod(int l, int r) const { return prod(l, r, (int)root.size() - 1); }
    S get(int i) const { return prod(i, i + 1); }

    // verAにverBの[l,r)を上書きした新しいverを作成する。
    int copy(int l, int r, int ver_a, int ver_b) {
        int nr = copy_range(root[ver_a], root[ver_b], 0, n, l, r);
        root.push_back(nr);
        return (int)root.size() - 1;
    }
};