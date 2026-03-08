// PENCILS Batch 1

#include <bits/stdc++.h>
using namespace std;

const int MAXC = 256;

static int grid[MAXC][MAXC][MAXC];
static int pre[MAXC][MAXC][MAXC];

int get_sum(int x1, int y1, int z1, int x2, int y2, int z2) {
    int res = pre[x2][y2][z2];

    if (x1 > 0) res -= pre[x1 - 1][y2][z2];
    if (y1 > 0) res -= pre[x2][y1 - 1][z2];
    if (z1 > 0) res -= pre[x2][y2][z1 - 1];

    if (x1 > 0 && y1 > 0) res += pre[x1 - 1][y1 - 1][z2];
    if (x1 > 0 && z1 > 0) res += pre[x1 - 1][y2][z1 - 1];
    if (y1 > 0 && z1 > 0) res += pre[x2][y1 - 1][z1 - 1];

    if (x1 > 0 && y1 > 0 && z1 > 0)
        res -= pre[x1 - 1][y1 - 1][z1 - 1];

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("PENCILS.INP", "r", stdin);
    freopen("PENCILS.OUT", "w", stdout);

    int n, k;
    cin >> n >> k;

    vector<tuple<int, int, int>> points(n);

    memset(grid, 0, sizeof(grid));

    for (int i = 0; i < n; i++) {
        int r, g, b;
        cin >> r >> g >> b;

        points[i] = {r, g, b};
        grid[r][g][b]++;
    }

    for (int i = 0; i < MAXC; i++) {
        for (int j = 0; j < MAXC; j++) {
            for (int z = 0; z < MAXC; z++) {

                pre[i][j][z] = grid[i][j][z];

                if (i > 0) pre[i][j][z] += pre[i - 1][j][z];
                if (j > 0) pre[i][j][z] += pre[i][j - 1][z];
                if (z > 0) pre[i][j][z] += pre[i][j][z - 1];

                if (i > 0 && j > 0) pre[i][j][z] -= pre[i - 1][j - 1][z];
                if (i > 0 && z > 0) pre[i][j][z] -= pre[i - 1][j][z - 1];
                if (j > 0 && z > 0) pre[i][j][z] -= pre[i][j - 1][z - 1];

                if (i > 0 && j > 0 && z > 0)
                    pre[i][j][z] += pre[i - 1][j - 1][z - 1];
            }
        }
    }

    int low = 0, high = 255;
    int bestD = 255;
    int best_x = -1, best_y = -1, best_z = -1;

    while (low <= high) {
        int mid = (low + high) / 2;

        bool found = false;
        int x0 = -1, y0 = -1, z0 = -1;

        for (int x = 0; x + mid < MAXC && !found; x++) {
            for (int y = 0; y + mid < MAXC && !found; y++) {
                for (int z = 0; z + mid < MAXC && !found; z++) {

                    if (get_sum(x, y, z, x + mid, y + mid, z + mid) >= k) {
                        found = true;
                        x0 = x;
                        y0 = y;
                        z0 = z;
                    }
                }
            }
        }

        if (found) {
            bestD = mid;
            best_x = x0;
            best_y = y0;
            best_z = z0;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    cout << bestD << "\n";

    int count = 0;

    for (auto [r, g, b] : points) {
        if (r >= best_x && r <= best_x + bestD &&
            g >= best_y && g <= best_y + bestD &&
            b >= best_z && b <= best_z + bestD) {

            cout << r << " " << g << " " << b << "\n";

            if (++count >= k) break;
        }
    }

    return 0;
}