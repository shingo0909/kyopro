#include <atcoder/segtree>
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int op(int a, int b) {
    return a + b;
}
int e() {
    return 0;
}

struct WaveletMatrixSeg {
  private:
    int H, N;
    vector<vector<int>> dat;
    using Seg = atcoder::segtree<int, op, e>;
    vector<Seg> seg;

  public:
    WaveletMatrixSeg(int H, vector<int> A, vector<int> X) : H(H), N(A.size()) {
        dat.assign(H, vector<int>(N + 1));
        seg.resize(H);
        for (int h = H - 1; h >= 0; h--) {
            vector<int> dir(N);
            vector<int> leftA, rightA;
            vector<int> leftX, rightX;
            for (int i = 0; i < N; i++) {
                dir[i] = A[i] >> h & 1;
                (dir[i] == 0 ? leftA : rightA).push_back(A[i]);
                (dir[i] == 0 ? leftX : rightX).push_back(X[i]);
            }

            int a = leftA.size(), b = rightA.size();

            for (int i = 0; i < a; i++) {
                A[i] = leftA[i];
                X[i] = leftX[i];
            }
            for (int i = 0; i < b; i++) {
                A[a + i] = rightA[i];
                X[a + i] = rightX[i];
            }

            for (int i = 0; i < N; i++)
                dat[h][i + 1] += dat[h][i] + dir[i];
            seg[h] = Seg(X);
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

    int next_pos(int h, int p) const {
        if (dat[h][p + 1] - dat[h][p] == 0) {
            return p - dat[h][p];
        } else {
            int right_offset = N - dat[h][N];
            return right_offset + dat[h][p];
        }
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

    void update_rec(int h, int p, int v) {
        if (h == 0)
            return;
        int q = next_pos(h - 1, p);
        seg[h - 1].set(q, v);
        update_rec(h - 1, q, v);
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

    ll sum_less_k_rec(int h, int l, int r, int k) {
        if (h == 0)
            return 0;
        auto [l0, r0, l1, r1] = get_subtree_range(h - 1, l, r);
        if (k >> (h - 1) & 1) {
            ll left_sum = seg[h - 1].prod(l0, r0);
            return left_sum + sum_less_k_rec(h - 1, l1, r1, k);
        } else {
            return sum_less_k_rec(h - 1, l0, r0, k);
        }
    }

  public:
    // Xの位置pの値をvに更新する
    void update(int p, int v) {
        update_rec(H, p, v);
    }

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