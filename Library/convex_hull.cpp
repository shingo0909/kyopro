#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct pos {
    ll x, y;
};

bool operator<(pos a, pos b) {
    if (a.x == b.x)
        return a.y < b.y;
    else
        return a.x < b.x;
}

ll cross(pos a, pos b, pos c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

ll inner(pos a, pos b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

vector<pos> convex_hull(vector<pos> ps) {
    int o = 0;
    for (int i = 0; i < int(ps.size()); i++) {
        if (ps[i] < ps[o])
            o = i;
    }
    pos c = ps[o];
    ps.erase(ps.begin() + o);
    sort(ps.begin(), ps.end(), [c](pos a, pos b) {
        ll cr = cross(a, b, c);
        if (cr == 0)
            return inner(a, c) < inner(b, c);
        else
            return cr > 0;
    });
    vector<pos> out = {c};
    for (pos p : ps) {
        while (true) {
            int n = out.size();
            if (n < 2 || cross(out[n - 2], out[n - 1], p) > 0) {
                break;
            }
            out.pop_back();
        }
        out.push_back(p);
    }
    return out;
}