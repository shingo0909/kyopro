#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<vector<ll>> mat_mul(vector<vector<ll>> a, vector<vector<ll>> b, ll m) {
    ll n = a.size();
    vector ans(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) {
                ans[i][j] += a[i][k] * b[k][j];
                ans[i][j] %= m;
            }
    return ans;
}

vector<vector<ll>> mat_pow(vector<vector<ll>> a, ll b, ll m) {
    ll n = a.size();
    vector ans(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++)
        ans[i][i] = 1;
    while (b) {
        if (b % 2)
            ans = mat_mul(ans, a, m);
        a = mat_mul(a, a, m);
        b /= 2;
    }

    return ans;
}