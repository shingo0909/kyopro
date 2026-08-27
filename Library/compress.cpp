// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/compress.cpp
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename... Vectors>
auto compress(Vectors... vecs) {
    vector<int> b;
    (b.insert(b.end(), vecs.begin(), vecs.end()), ...);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());

    auto enc = [&](vector<int> a) {
        vector<int> res(a.size());
        for (int i = 0; i < (int)a.size(); i++) {
            res[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        }
        return res;
    };

    return make_tuple(enc(vecs)...);
}