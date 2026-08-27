// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/BinaryTrie.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct BinaryTrie {
  private:
    static constexpr int H = 31;
    struct Node {
        int nxt[2];
        int cnt;
        Node() : cnt(0) {
            nxt[0] = -1;
            nxt[1] = -1;
        };
    };
    vector<Node> nodes;

    int new_node() {
        nodes.push_back(Node());
        return (int)nodes.size() - 1;
    }

    void add_rec(int h, int x, int cur) {
        nodes[cur].cnt++;
        if (h == 0)
            return;
        int f = x >> (h - 1) & 1;
        if (nodes[cur].nxt[f] == -1) {
            nodes[cur].nxt[f] = new_node();
        }
        add_rec(h - 1, x, nodes[cur].nxt[f]);
    }
    void erase_rec(int h, int x, int cur) {
        nodes[cur].cnt--;
        if (h == 0)
            return;
        int f = x >> (h - 1) & 1;
        add_rec(h - 1, x, nodes[cur].nxt[f]);
    }

    int count_rec(int h, int x, int cur) {
        if (h == 0)
            return nodes[cur].cnt;
        int f = x >> (h - 1) & 1;
        if (nodes[cur].nxt[f] == -1) {
            return 0;
        }
        return count_rec(h - 1, x, nodes[cur].nxt[f]);
    }

    int count_less_rec(int h, int x, int xor_val, int cur) {
        if (h == 0)
            return 0;
        int ret = 0;
        int f = (xor_val >> (h - 1)) & 1;
        if (x >> (h - 1) & 1 && nodes[cur].nxt[f] != -1)
            ret += nodes[nodes[cur].nxt[f]].cnt;
        if (nodes[cur].nxt[f ^ (x >> (h - 1) & 1)] != -1)
            ret += count_less_rec(h - 1, x, xor_val, nodes[cur].nxt[f ^ (x >> (h - 1) & 1)]);
        return ret;
    }

  public:
    BinaryTrie() {
        nodes.push_back(Node());
    }
    void add(int x) {
        add_rec(H, x, 0);
    }
    void erase(int x) {
        if (count(x) == 0) {
            return;
        }
        erase_rec(H, x, 0);
    }
    int count(int x) {
        return count_rec(H, x, 0);
    }
    int count_less(int x, int xor_val = 0) {
        return count_less_rec(H, x, xor_val, 0);
    }
};