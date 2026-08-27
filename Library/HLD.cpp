// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/HLD.cpp
#include <atcoder/all>
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct HLD {
  private:
    int n;
    vector<int> siz;
    vector<vector<int>> g;
    vector<vector<int>> child;
    vector<int> parent;
    vector<int> head;
    vector<int> pre;
    vector<int> order;
    vector<int> dep;

    void dfs(int i, int p) {
        parent[i] = p;
        for (int j : g[i]) {
            if (j == p)
                continue;
            child[i].push_back(j);
            dep[j] = dep[i] + 1;
            dfs(j, i);
        }
        return;
    }
    void dfs2(int v, int a) {
        pre[v] = order.size();
        order.push_back(v);
        head[v] = a;

        if (child[v].empty())
            return;
        int m = 0;
        int ind = -1;
        for (int i : child[v]) {
            if (size(i) > m) {
                m = size(i);
                ind = i;
            }
        }
        dfs2(ind, a);

        for (int i : child[v]) {
            if (i == ind)
                continue;
            dfs2(i, i);
        }
    }

  public:
    HLD(int n) : n(n) {
        child.resize(n);
        g.resize(n);
        head.resize(n);
        siz.assign(n, 0);
        pre.resize(n);
        order.reserve(n);
        dep.assign(n, 0);
        parent.resize(n);
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        return;
    }

    void build() {
        dfs(0, -1);
        dfs2(0, 0);
    }

    // u-v パス上の頂点集合を HLD 上の半開区間の vector で返す
    // lca : lca を含むかどうか。辺を考えたいときに有効
    vector<pair<int, int>> const path_query(int u, int v, bool lca = true) {
        vector<pair<int, int>> ret;
        while (head[u] != head[v]) {
            if (dep[head[u]] <= dep[head[v]]) {
                ret.push_back({pre[head[v]], pre[v] + 1});
                v = parent[head[v]];
            } else {
                ret.push_back({pre[head[u]], pre[u] + 1});
                u = parent[head[u]];
            }
        }
        if (dep[u] > dep[v])
            swap(u, v);
        if (lca)
            ret.push_back({pre[u], pre[v] + 1});
        else if (pre[u] + 1 <= pre[v])
            ret.push_back({pre[u] + 1, pre[v] + 1});
        return ret;
    }
    // 頂点 u の部分木内の頂点集合を HLD 上の半開区間で返す
    // lca : lca を含むかどうか。辺を考えたいときに有効
    pair<int, int> const subtree_query(int u, bool lca = true) {
        if (lca) {
            return {pre[u], pre[u] + size(u)};
        } else {
            return {pre[u] + 1, pre[u] + size(u)};
        }
    }
    // 頂点番号 -> HLD上の位置
    int pos(int i) const {
        return pre[i];
    }
    // HLD上の位置 -> 頂点番号
    int kth(int k) const {
        return order[k];
    }
    int size(int v) {
        if (siz[v] != 0)
            return siz[v];
        siz[v] = 1;
        for (int i : child[v])
            siz[v] += size(i);
        return siz[v];
    }
    int depth(int v) const {
        return dep[v];
    }
};
