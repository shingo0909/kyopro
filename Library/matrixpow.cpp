// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/matrixpow.cpp
#include <atcoder/modint>
#include <bits/stdc++.h>

using namespace std;

using mint = atcoder::modint998244353;

vector<vector<mint>> matrix_product(vector<vector<mint>> &a, vector<vector<mint>> &b) {
    int n = a.size();
    vector<vector<mint>> ans(n, vector<mint>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++) {
                ans[i][j] += a[i][k] * b[k][j];
            }
    return ans;
}

vector<vector<mint>> matrixpow(vector<vector<mint>> a, long long k) {
    int n = a.size();
    vector<vector<mint>> ans(n, vector<mint>(n, 0));
    for (int i = 0; i < n; i++)
        ans[i][i] = 1;

    while (k > 0) {
        if (k % 2) {
            ans = matrix_product(ans, a);
        }
        k /= 2;
        a = matrix_product(a, a);
    }
    return ans;
}