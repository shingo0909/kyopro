#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SSSP {
  private:
    struct Edge {
        int to;
        ll cost;
    };

    int n;
    vector<vector<Edge>> adj;
    vector<ll> d;
    vector<int> prev_node;
    static constexpr ll INF = 1LL << 62;

  public:
    explicit SSSP(int n) : n(n), adj(n) {}

    void add_edge(int from, int to, ll cost = 1) {
        adj[from].push_back({to, cost});
    }

    void reset() {
        d.assign(n, INF);
        prev_node.assign(n, -1);
    }
    // BFS
    void bfs(int s) {
        reset();
        queue<int> q;
        d[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &e : adj[v]) {
                if (d[e.to] != INF)
                    continue;
                d[e.to] = d[v] + 1;
                prev_node[e.to] = v;
                q.push(e.to);
            }
        }
    }
    // 01BFS
    void zero_one_bfs(int s) {
        reset();
        deque<int> q;
        d[s] = 0;
        q.push_back(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            for (auto &e : adj[v]) {
                ll nd = d[v] + e.cost;
                if (nd >= d[e.to])
                    continue;
                d[e.to] = nd;
                prev_node[e.to] = v;
                if (e.cost == 0)
                    q.push_front(e.to);
                else
                    q.push_back(e.to);
            }
        }
    }

    // dijkstra
    void dijkstra(int s) {
        reset();
        using P = pair<ll, int>;
        priority_queue<P, vector<P>, greater<P>> pq;
        d[s] = 0;
        pq.push({0, s});
        while (!pq.empty()) {
            auto [cost, v] = pq.top();
            pq.pop();
            if (cost > d[v])
                continue;
            for (auto &e : adj[v]) {
                ll nd = d[v] + e.cost;
                if (nd >= d[e.to])
                    continue;
                d[e.to] = nd;
                prev_node[e.to] = v;
                pq.push({nd, e.to});
            }
        }
    }

    // Bellman-Ford
    // 負閉路から到達できる頂点のdistは-INF
    // 戻り値: 負閉路が存在すれば true
    bool bellman_ford(int s) {
        reset();
        d[s] = 0;
        vector<tuple<int, int, ll>> edges;
        for (int v = 0; v < n; v++)
            for (auto &e : adj[v])
                edges.emplace_back(v, e.to, e.cost);

        for (int i = 0; i < n; i++) {
            bool updated = false;
            for (auto &[from, to, cost] : edges) {
                if (d[from] == INF)
                    continue;
                if (d[from] + cost < d[to]) {
                    d[to] = d[from] + cost;
                    prev_node[to] = from;
                    updated = true;
                    if (i == n - 1)
                        d[to] = -INF;
                }
            }
            if (!updated)
                break;
        }

        queue<int> q;
        for (int v = 0; v < n; v++)
            if (d[v] == -INF)
                q.push(v);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &e : adj[v]) {
                if (d[e.to] != -INF) {
                    d[e.to] = -INF;
                    q.push(e.to);
                }
            }
        }

        bool has_negative_cycle = false;
        for (int v = 0; v < n; v++)
            if (d[v] == -INF) {
                has_negative_cycle = true;
                break;
            }
        return has_negative_cycle;
    }

    ll dist(int v) const {
        if (d[v] == INF)
            return -1;
        if (d[v] == -INF)
            return -2;
        return d[v];
    }

    vector<int> path(int g) const {
        if (d[g] == INF || d[g] == -INF)
            return {};
        vector<int> res;
        for (int v = g; v != -1; v = prev_node[v])
            res.push_back(v);
        reverse(res.begin(), res.end());
        return res;
    }
};