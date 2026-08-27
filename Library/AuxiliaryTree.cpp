#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct AuxiliaryTree {
    int n, log, timer;
    vector<vector<int>> g, parent;
    vector<vector<pair<int, int>>> aux;
    vector<int> depth, in, out;

    AuxiliaryTree(int n_) : n(n_) {
        g.resize(n);
        aux.resize(n);
        depth.resize(n);
        in.resize(n);
        out.resize(n);

        log = 0, timer = 0;
        while ((1 << log) <= n)
            log++;
        parent.assign(log, vector<int>(n, -1));
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        return;
    }

    void dfs(int v, int p) {
        parent[0][v] = p;
        in[v] = timer++;
        for (int u : g[v]) {
            if (u == p)
                continue;
            depth[u] = depth[v] + 1;
            dfs(u, v);
        }
        out[v] = timer++;
        return;
    }

    void init() {
        depth[0] = 0;
        dfs(0, -1);
        for (int k = 0; k + 1 < log; k++) {
            for (int i = 0; i < n; i++) {
                if (parent[k][i] == -1) {
                    parent[k + 1][i] = -1;
                } else {
                    parent[k + 1][i] = parent[k][parent[k][i]];
                }
            }
        }
        return;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v])
            swap(u, v);
        int d = depth[u] - depth[v];
        for (int k = 0; k < log; k++) {
            if (d & (1 << k))
                u = parent[k][u];
        }
        if (u == v)
            return u;
        for (int k = log - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    int dist(int u, int v) {
        int w = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }

    bool is_ancestor(int u, int v) {
        return in[u] <= in[v] && out[v] <= out[u];
    }

    // 根は必ず0
    void build_aux(vector<int> s) {
        // 0は入れておく
        s.push_back(0);
        sort(s.begin(), s.end(), [&](int a, int b) {
            return in[a] < in[b];
        });

        // LCAを追加
        int size = s.size();
        for (int i = 0; i < size - 1; i++) {
            s.push_back(lca(s[i], s[i + 1]));
        }

        // 重複削除
        sort(s.begin(), s.end(), [&](int a, int b) {
            return in[a] < in[b];
        });
        s.erase(unique(s.begin(), s.end()), s.end());

        // 使う頂点だけ掃除
        for (int v : s)
            aux[v].clear();

        stack<int> st;
        for (int v : s) {
            while (!st.empty() && !is_ancestor(st.top(), v))
                st.pop();
            if (!st.empty()) {
                aux[st.top()].push_back(make_pair(v, dist(st.top(), v)));
            }
            st.push(v);
        }
        return;
    }
};