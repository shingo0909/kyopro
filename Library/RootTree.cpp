// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/RootTree.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct RootTree {
    int n, LOG;
    vector<vector<int>> g, parent;
    vector<int> depth;
    RootTree(int n) : n(n), g(n), depth(n) {
        LOG = 1;
        while ((1 << LOG) <= n)
            LOG++;
        parent.assign(LOG, vector<int>(n, -1));
    }
    void add_edge(int u, int v) {
        g[u].push_back(v);
        return;
    }

    void dfs(int i, int p, int d) {
        parent[0][i] = p;
        depth[i] = d;
        for (int j : g[i]) {
            if (j == p)
                continue;
            dfs(j, i, d + 1);
        }
        return;
    }

    void build(int root) {
        dfs(root, -1, 0);
        for (int j = 0; j + 1 < LOG; j++) {
            for (int i = 0; i < n; i++) {
                if (parent[j][i] != -1) {
                    parent[j + 1][i] = parent[j][parent[j][i]];
                }
            }
        }
        return;
    }

    int lca(int a, int b) {
        if (depth[a] < depth[b])
            swap(a, b);
        int d = depth[a] - depth[b];
        for (int j = 0; j < LOG; j++) {
            if ((d >> j) & 1) {
                a = parent[j][a];
            }
        }
        if (a == b)
            return a;
        for (int j = LOG - 1; j >= 0; j--) {
            if (parent[j][a] != parent[j][b]) {
                a = parent[j][a];
                b = parent[j][b];
            }
        }
        return parent[0][a];
    }

    int dist(int a, int b) {
        int c = lca(a, b);
        return depth[a] + depth[b] - 2 * depth[c];
    }

    int kth_ancestor(int v, int k) {
        if (depth[v] < k)
            return -1;
        for (int j = 0; j < LOG; j++) {
            if ((k >> j) & 1) {
                v = parent[j][v];
            }
        }
        return v;
    }
};