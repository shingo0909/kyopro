#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 参考:https://algo-logic.info/tree-dp/
struct Rerooting {

    /*ここからを問題ごとに書き換える*/
    // DPの型
    struct DP {
        ll dp;
        DP(ll dp_) : dp(dp_) {}
    };
    // 単位元
    DP identity = DP(0);
    // 頂点のマージ
    function<DP(DP, DP)> merge = [](DP a, DP b) -> DP {
        return DP(max(a.dp, b.dp));
    };
    // マージしたDPを使って遷移
    // 頂点情報・辺情報も参照可能
    function<DP(DP, int, ll)> add_root = [this](DP a, int v, ll w) -> DP {
        return DP(max(a.dp, ver[v]) + w);
    };
    /*ここまで*/

    struct edge {
        int t;
        ll w;
    };

    vector<vector<DP>> dp;
    vector<DP> ans;
    vector<vector<edge>> g;
    vector<ll> ver;

    Rerooting(int n_) {
        dp.resize(n_);
        ans.assign(n_, identity);
        g.resize(n_);
        ver.assign(n_, 0);
    }

    void add_edge(int a, int b, ll w = 0) {
        g[a].push_back({b, w});
    }
    void set_vertex(int a, ll w) {
        ver[a] = w;
    }
    void solve() {
        dfs1(0, -1, 0);
        dfs2(0, identity, -1);
    }

    DP dfs1(int v, int p, ll pw) {
        DP dp_cum = identity;
        int deg = g[v].size();
        dp[v].assign(deg, identity);
        for (int i = 0; i < deg; i++) {
            auto [t, w] = g[v][i];
            if (t == p)
                continue;
            dp[v][i] = dfs1(t, v, w);
            dp_cum = merge(dp_cum, dp[v][i]);
        }
        return add_root(dp_cum, v, pw);
    }

    void dfs2(int v, DP dp_p, int p) {
        int deg = g[v].size();
        for (int i = 0; i < deg; i++) {
            if (g[v][i].t == p)
                dp[v][i] = dp_p;
        }
        vector<DP> dp_l(deg + 1, identity);
        for (int i = 0; i < deg; i++) {
            dp_l[i + 1] = merge(dp_l[i], dp[v][i]);
        }
        vector<DP> dp_r(deg + 1, identity);
        for (int i = deg - 1; i >= 0; i--) {
            dp_r[i] = merge(dp_r[i + 1], dp[v][i]);
        }
        ans[v] = add_root(dp_l[deg], v, 0);
        for (int i = 0; i < deg; i++) {
            auto [t, w] = g[v][i];
            if (t == p)
                continue;
            dfs2(t, add_root(merge(dp_l[i], dp_r[i + 1]), v, w), v);
        }
        return;
    }
};