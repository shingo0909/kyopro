// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/Trie.cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Trie {
    struct Node {
        vector<int> next, accept;
        int c, common;
        Node(int c_) : c(c_), common(0) {
            next.assign(26, -1);
        }
    };
    vector<Node> nodes;
    int root;
    Trie() : root(0) {
        nodes.push_back(Node(root));
    }

    void insert(string s) {
        int id = 0;
        for (char c : s) {
            int num = c - 'a';
            int &nid = nodes[id].next[num];
            if (nid == -1) {
                nid = nodes.size();
                nodes.push_back(Node(num));
            }
            nodes[id].common++;
            id = nid;
        }
        nodes[id].common++;
        nodes[id].accept.push_back(nodes[0].common);
    }
    bool search(string s) {
        int id = 0;
        for (char c : s) {
            int num = c - 'a';
            int nid = nodes[id].next[num];
            if (nid == -1) {
                return false;
            }
            id = nid;
        }
        return nodes[id].accept.size() > 0;
    }
};