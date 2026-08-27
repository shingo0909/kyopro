#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class UnionFind {
  public:
    vector<int> parent, size;
    std::vector<ll> pot;

    UnionFind(int n) : parent(n, -1), size(n, 1), pot(n, 0) {}

    int leader(int x) {
        if (parent[x] == -1)
            return x;
        int l = leader(parent[x]);
        pot[x] = pot[parent[x]] + pot[x];
        parent[x] = l;
        return parent[x] = leader(parent[x]);
    }

    bool merge(int x, int y, ll d) {
        d += potential(x);
        d -= potential(y);
        int lex = leader(x);
        int ley = leader(y);
        if (lex == ley)
            return d == diff(lex, ley);
        if (lex > ley) {
            swap(lex, ley);
            d = -d;
        }
        parent[ley] = lex;
        size[lex] += size[ley];
        pot[ley] = d;
        return true;
    }

    bool same(int x, int y) {
        return leader(x) == leader(y);
    }

    int get_size(int x) {
        return size[leader(x)];
    }

    ll potential(int x) {
        leader(x);
        return pot[x];
    }

    ll diff(int x, int y) {
        return potential(y) - potential(x);
    }
};