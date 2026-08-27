#include <atcoder/modint>
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using mint = atcoder::modint998244353;

vector<vector<mint>> mat_mul(vector<vector<mint>> a, vector<vector<mint>> b) {
    int n = a.size();
    vector ans(n, vector<mint>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) {
                ans[i][j] += a[i][k] * b[k][j];
            }
    return ans;
}

vector<vector<mint>> mat_pow(vector<vector<mint>> a, ll b) {
    int n = a.size();
    vector ans(n, vector<mint>(n, 0));
    for (int i = 0; i < n; i++)
        ans[i][i] = 1;
    while (b) {
        if (b % 2)
            ans = mat_mul(ans, a);
        a = mat_mul(a, a);
        b /= 2;
    }

    return ans;
}