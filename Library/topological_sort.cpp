// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/topological_sort.cpp
#include <bits/stdc++.h>

using namespace std;

vector<int> topological_sort(vector<vector<int>> &g) {
    int n = g.size();
    vector<int> in(n, 0);
    for (auto i : g) {
        for (int j : i) {
            in[j]++;
        }
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (in[i] == 0)
            q.push(i);
    }
    vector<int> ans;
    while (q.size() > 0) {
        int from = q.front();
        ans.push_back(from);
        q.pop();
        for (int i : g[from]) {
            in[i]--;
            if (in[i] == 0)
                q.push(i);
        }
    }
    return ans;
}