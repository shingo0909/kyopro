#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <class S, S (*op)(S, S), S (*e)()>
struct PersistentSegTree {
  private:
    struct Node {
        int l, r;
        S val;
        Node(int l_, int r_, S val_) : l(l_), r(r_), val(val_) {}
    };
    int n;
    vector<Node> pool;
    vector<int> root;

    int new_node(const Node &v) {
        pool.push_back(v);
        return (int)pool.size() - 1;
    }

    int build(int l, int r) {
        if (l + 1 == r) {
            return new_node(Node(-1, -1, e()));
        }

        int m = (l + r) / 2;
        int node_l = build(l, m);
        int node_r = build(m, r);

        return new_node(
            Node(node_l, node_r, op(pool[node_l].val, pool[node_r].val)));
    }

    int build_vec(int l, int r, vector<S> &vec) {
        if (l + 1 == r) {
            return new_node(Node(-1, -1, vec[l]));
        }

        int m = (l + r) / 2;
        int node_l = build_vec(l, m, vec);
        int node_r = build_vec(m, r, vec);

        return new_node(
            Node({node_l, node_r, op(pool[node_l].val, pool[node_r].val)}));
    }

    int update(int cur, int l, int r, int pos, S x) {
        Node node = pool[cur];
        if (l + 1 == r) {
            node.val = x;
            return new_node(node);
        }
        int m = (l + r) / 2;
        if (pos < m)
            node.l = update(node.l, l, m, pos, x);
        else
            node.r = update(node.r, m, r, pos, x);
        node.val = op(pool[node.l].val, pool[node.r].val);
        return new_node(node);
    }

    S query(int node, int l, int r, int ql, int qr) const {
        if (qr <= l || r <= ql)
            return e();
        if (ql <= l && r <= qr)
            return pool[node].val;

        int m = (l + r) / 2;
        return op(query(pool[node].l, l, m, ql, qr),
                  query(pool[node].r, m, r, ql, qr));
    }

    int copy_range(int cur_a, int cur_b, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql)
            return cur_a;
        if (ql <= l && r <= qr)
            return cur_b;

        Node na = pool[cur_a];
        Node nb = pool[cur_b];

        int m = (l + r) / 2;
        int new_l = copy_range(na.l, nb.l, l, m, ql, qr);
        int new_r = copy_range(na.r, nb.r, m, r, ql, qr);

        return new_node(Node(new_l, new_r, op(pool[new_l].val, pool[new_r].val)));
    }

    int kth_dfs(int node_l, int node_r,
                int l, int r, int k) const {
        if (l + 1 == r)
            return l;

        int m = (l + r) / 2;
        int left_l = pool[node_l].l;
        int left_r = pool[node_r].l;

        S cnt_left =
            pool[left_r].val - pool[left_l].val;
        if (k <= cnt_left) {
            return kth_dfs(left_l, left_r, l, m, k);
        } else {
            int right_l = pool[node_l].r;
            int right_r = pool[node_r].r;
            return kth_dfs(right_l, right_r, m, r, k - cnt_left);
        }
    }

  public:
    // 単位元e()で構築
    PersistentSegTree(int N) : n(N) { root.push_back(build(0, n)); }
    // 配列vector<S>から構築
    PersistentSegTree(const vector<S> &v) : n(v.size()) {
        root.push_back(build_vec(0, n, v));
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
    S prod(int l, int r, int ver) const { return query(root[ver], 0, n, l, r); }
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

    // 区間k番目の値を調べる。配列のprefixの頻度列を各verで持つように構築してから使う。
    int kth(int l, int r, int k) {
        return kth_dfs(root[l], root[r], 0, n, k);
    }
};