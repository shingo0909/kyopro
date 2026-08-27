// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/unionfind.cpp
#include <bits/stdc++.h>
using namespace std;

class UnionFind {
  public:
    vector<int> parent, size;

    UnionFind(int n) : parent(n, -1), size(n, 1) {}

    int leader(int x) {
        if (parent[x] == -1)
            return x;
        return parent[x] = leader(parent[x]);
    }

    bool merge(int x, int y) {
        int lex = leader(x);
        int ley = leader(y);
        if (lex == ley)
            return false;
        if (lex > ley)
            swap(lex, ley);
        parent[ley] = lex;
        size[lex] += size[ley];
        return true;
    }

    bool same(int x, int y) {
        return leader(x) == leader(y);
    }

    int get_size(int x) {
        return size[leader(x)];
    }
};