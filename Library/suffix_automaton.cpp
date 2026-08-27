#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct SuffixAutomaton {
    struct State {
        unordered_map<char, int> next;
        int link;
        int len;
        State() : link(-1), len(0) {};
    };

    vector<State> st;
    int last;
    SuffixAutomaton() {
        st.push_back(State());
        last = 0;
    }

    SuffixAutomaton(string s) : SuffixAutomaton() {
        for (char c : s)
            add_char(c);
    }

    void add_char(char c) {
        int cur = st.size();
        st.push_back(State());
        st[cur].len = st[last].len + 1;

        int p = last;

        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];

            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;

                while (p != -1 && st[p].next.count(c) && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = clone;
                st[cur].link = clone;
            }
        }
        last = cur;
    }
};