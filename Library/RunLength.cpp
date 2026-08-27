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