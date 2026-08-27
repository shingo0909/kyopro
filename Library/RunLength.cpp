// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/RunLength.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<pair<char, int>> run_length(string s) {
    int n = s.size();
    vector<pair<char, int>> ans;
    ans.push_back({s[0], 1});
    for (int i = 1; i < n; i++) {
        if (s[i] == ans.back().first) {
            ans.back().second++;
        } else {
            ans.push_back({s[i], 1});
        }
    }
    return ans;
}