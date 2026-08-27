#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace zeta_mobius {

template <class T = ll>
vector<T> subset_zeta(vector<T> v) {
    int n = v.size();
    for (int i = 0; (1 << i) < n; i++) {
        for (int s = 0; s < n; s++) {
            if (s >> i & 1)
                v[s] += v[s ^ (1 << i)];
        }
    }
    return v;
}

template <class T = ll>
vector<T> subset_mobius(vector<T> v) {
    int n = v.size();
    for (int i = 0; (1 << i) < n; i++) {
        for (int s = 0; s < n; s++) {
            if (s >> i & 1)
                v[s] -= v[s ^ (1 << i)];
        }
    }
    return v;
}

template <class T = ll>
vector<T> superset_zeta(vector<T> v) {
    int n = v.size();
    for (int i = 0; (1 << i) < n; i++) {
        for (int s = 0; s < n; s++) {
            if (!(s >> i & 1))
                v[s] += v[s ^ (1 << i)];
        }
    }
    return v;
}

template <class T = ll>
vector<T> superset_mobius(vector<T> v) {
    int n = v.size();
    for (int i = 0; (1 << i) < n; i++) {
        for (int s = 0; s < n; s++) {
            if (!(s >> i & 1))
                v[s] -= v[s ^ (1 << i)];
        }
    }
    return v;
}

template <class T = ll>
vector<T> or_convolution(vector<T> a, vector<T> b) {
    assert(a.size() == b.size());
    a = subset_zeta(a);
    b = subset_zeta(b);
    for (int i = 0; i < (int)a.size(); i++)
        a[i] *= b[i];
    a = subset_mobius(a);
    return a;
}

template <class T = ll>
vector<T> and_convolution(vector<T> a, vector<T> b) {
    assert(a.size() == b.size());
    a = superset_zeta(a);
    b = superset_zeta(b);
    for (int i = 0; i < (int)a.size(); i++)
        a[i] *= b[i];
    a = superset_mobius(a);
    return a;
}

} // namespace zeta_mobius