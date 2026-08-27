#include <bits/stdc++.h>
using namespace std;

struct doubling {
    vector<vector<int>> d;
    int n;
    doubling(vector<int> p) : d(60, vector<int>(p.size())) {
        n = p.size();
        d[0] = p;
        for (int i = 1; i < 60; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = d[i - 1][d[i - 1][j]];
            }
        }
    }
    int get_ans(int x, long long t) {
        for (int i = 0; i < 60; i++) {
            if ((t >> i) % 2) {
                x = d[i][x];
            }
        }
        return x;
    }
};