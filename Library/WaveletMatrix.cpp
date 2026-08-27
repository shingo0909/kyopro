// https://github.com/shingo0909/kyopro/blob/39029fab39c1735c38e5e9e4494d9934f81d6918/Library/WaveletMatrix.cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct WaveletMatrix {
  private:
    int H, N;
    vector<vector<int>> dat;
    vector<vector<ll>> sum;

  public:
    WaveletMatrix(int H, vector<int> A) : H(H), N(A.size()) {
        sum.assign(H, vector<ll>(N + 1));
        dat.assign(H, vector<int>(N + 1));
        for (int h = H - 1; h >= 0; h--) {
            vector<int> dir(N);
            vector<int> left, right;
            for (int i = 0; i < N; i++) {
                dir[i] = A[i] >> h & 1;
                (dir[i] == 0 ? left : right).push_back(A[i]);
            }

            int a = left.size(), b = right.size();

            for (int i = 0; i < a; i++)
                A[i] = left[i];
            for (int i = 0; i < b; i++)
                A[a + i] = right[i];

            for (int i = 0; i < N; i++)
                dat[h][i + 1] += dat[h][i] + dir[i];
            for (int i = 0; i < N; i++)
                sum[h][i + 1] += sum[h][i] + A[i];
        }
    }

  private:
    // 高さh+1、区間[l, r)の子を求める。
    tuple<int, int, int, int> get_subtree_range(int h, int l, int r) const {
        int a0 = l - dat[h][l], a1 = dat[h][l];
        int b0 = r - dat[h][r], b1 = dat[h][r];
        int c0 = N - dat[h][N];
        return {a0, b0, c0 + a1, c0 + b1};
    }

    int kth_smallest_rec(int h, int l, int r, int k) const {
        if (h == 0)
            return 0;
        auto [l0, r0, l1, r1] = get_subtree_range(h - 1, l, r);
        int left_size = r0 - l0;
        if (k < left_size) {
            return kth_smallest_rec(h - 1, l0, r0, k);
        } else {
            return (1 << (h - 1)) + kth_smallest_rec(h - 1, l1, r1, k - left_size);
        }
    }

    int cnt_less_k_rec(int h, int l, int r, int k) const {
        if (h == 0)
            return 0;
        auto [l0, r0, l1, r1] = get_subtree_range(h - 1, l, r);
        int left_size = r0 - l0;
        if (k >> (h - 1) & 1) {
            return left_size + cnt_less_k_rec(h - 1, l1, r1, k);
        } else {
            return cnt_less_k_rec(h - 1, l0, r0, k);
        }
    }

    ll sum_less_k_rec(int h, int l, int r, int k) const {
        if (h == 0)
            return 0;
        auto [l0, r0, l1, r1] = get_subtree_range(h - 1, l, r);
        ll left_sum = sum[h - 1][r0] - sum[h - 1][l0];
        if (k >> (h - 1) & 1) {
            return left_sum + sum_less_k_rec(h - 1, l1, r1, k);
        } else {
            return sum_less_k_rec(h - 1, l0, r0, k);
        }
    }

  public:
    int kth_smallest(int l, int r, int k) {
        return kth_smallest_rec(H, l, r, k);
    }

    int cnt_less_k(int l, int r, int k) {
        return cnt_less_k_rec(H, l, r, k);
    }
    ll sum_less_k(int l, int r, int k) {
        return sum_less_k_rec(H, l, r, k);
    }
};
