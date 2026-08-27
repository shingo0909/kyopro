#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 正規化したxor基底を降順で出力
template <class T>
vector<T> xor_basis(vector<T> v) {
    vector<T> basis;
    for (T x : v) {
        for (T b : basis)
            x = min(x, x ^ b);
        if (x > 0)
            basis.push_back(x);
    }
    int n = basis.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            basis[i] = min(basis[i], basis[i] ^ basis[j]);
        }
    }
    sort(basis.rbegin(), basis.rend());
    return basis;
}
