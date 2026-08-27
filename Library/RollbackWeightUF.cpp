#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct RollbackUF {
  private:
    int n;
    vector<int> parent;
    vector<ll> diffWeight;
    stack<tuple<int, int, int>> history;
    int comps;

  public:
    RollbackUF(int n) : n(n), parent(n, -1), diffWeight(n, 0), comps(n) {}

    pair<int, ll> find(int x) {
        ll w = 0;
        while (parent[x] >= 0) {
            w += diffWeight[x];
            x = parent[x];
        }
        return {x, w};
    }

    int leader(int x) {
        return find(x).first;
    }

    ll weight(int x) {
        return find(x).second;
    }

    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    // 既にsame(a,b)である前提
    ll diff(int a, int b) {
        return weight(b) - weight(a);
    }
    // weight(b) - weight(a) = w となるように merge
    // 矛盾があればfalse それ以外はtrue
    bool merge(int a, int b, ll w) {
        auto [ra, wa] = find(a);
        auto [rb, wb] = find(b);
        if (ra == rb) {
            history.emplace(-1, -1, 0LL);
            return (wb - wa) == w;
        }

        ll dB = wa + w - wb;
        int A = ra, B = rb;

        if (parent[A] > parent[B]) {
            swap(A, B);
            dB = -dB;
        }

        history.emplace(A, parent[A], diffWeight[A]);
        history.emplace(B, parent[B], diffWeight[B]);

        parent[A] += parent[B];
        diffWeight[B] = dB;
        parent[B] = A;
        comps--;
        return true;
    }

    void rollback() {
        assert(!history.empty());
        auto [j, w, dw] = history.top();
        history.pop();

        if (j == -1)
            return;

        auto [i, v, dv] = history.top();
        history.pop();

        parent[j] = w;
        diffWeight[j] = dw;
        parent[i] = v;
        diffWeight[i] = dv;
        comps++;
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
