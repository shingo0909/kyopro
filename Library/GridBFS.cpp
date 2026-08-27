#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct GridBFS {
  private:
    int H, W;
    vector<string> grid;
    vector<vector<ll>> d;

    static constexpr ll INF = 1LL << 62;
    static constexpr int dx[] = {0, 0, 1, -1};
    static constexpr int dy[] = {1, -1, 0, 0};

  public:
    GridBFS(vector<string> &grid)
        : H(grid.size()), W(grid[0].size()), grid(grid) {}

    void bfs(int sx, int sy) {
        d.assign(H, vector<ll>(W, INF));
        queue<pair<int, int>> q;
        d[sx][sy] = 0;
        q.push({sx, sy});
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                if (nx < 0 || nx >= H || ny < 0 || ny >= W)
                    continue;
                if (grid[nx][ny] == '#')
                    continue;
                if (d[nx][ny] != INF)
                    continue;
                d[nx][ny] = d[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    ll dist(int x, int y) const {
        return d[x][y] == INF ? -1 : d[x][y];
    }
};