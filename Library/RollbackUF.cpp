#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct RollbackUF {
  private:
    int n;
    vector<int> parent;
    stack<pair<int, int>> history;
    int comps;

  public:
    RollbackUF(int n) : n(n), parent(n, -1), comps(n) {}

    int leader(int x) {
        while (parent[x] >= 0)
            x = parent[x];
        return x;
    }

    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    bool merge(int a, int b) {
        a = leader(a);
        b = leader(b);
        if (a == b) {
            history.emplace(-1, -1);
            return false;
        }
        if (parent[a] > parent[b])
            swap(a, b);

        history.emplace(a, parent[a]);
        history.emplace(b, parent[b]);

        parent[a] += parent[b];
        parent[b] = a;
        comps--;
        return true;
    }
    void rollback() {
        assert(!history.empty());
        auto [j, w] = history.top();
        history.pop();

        if (j == -1)
            return;

        auto [i, v] = history.top();
        history.pop();
        parent[j] = w;
        parent[i] = v;
        comps++;
        return;
    }
    // 頂点xが属する連結成分のサイズ
    int size(int x) {
        return -parent[leader(x)];
    }
    // 連結成分数
    int components() {
        return comps;
    }
};
