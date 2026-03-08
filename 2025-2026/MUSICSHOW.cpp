// MUSICSHOW FULL

#include <bits/stdc++.h>
#define taskname "MUSICSHOW"

using namespace std;

struct Object {
    int p, c, x;

    Object(int p = 0, int c = 0, int x = 0)
        : p(p), c(c), x(x) {}

    bool operator<(const Object &other) const {
        return (x == other.x && p == other.p ? c < other.c :
               (x == other.x ? p < other.p :
                               x < other.x));
    }
};

const int MAX_N = int(2'000);

int n, a, b;
int dp[MAX_N + 5][2 * MAX_N + 5];
Object arr[MAX_N + 5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef LOCAL
    // freopen(".inp", "r", stdin);
    // freopen(".out", "w", stdout);
#endif

#ifdef ONLINE_JUDGE
    freopen(taskname ".inp", "r", stdin);
    freopen(taskname ".out", "w", stdout);
#endif

    cin >> n >> a >> b;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i].p >> arr[i].c >> arr[i].x;
    }

    sort(arr + 1, arr + n + 1);

    memset(dp, -1, sizeof(dp));
    dp[1][a + b] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= a + b; j++) {

            if (dp[i][j] == -1) continue;

            int p = arr[i].p;
            int c = arr[i].c;
            int x = arr[i].x;

            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);

            if (j - c * x >= a) {
                dp[i + 1][j - c * x] = max(dp[i + 1][j - c * x], dp[i][j] + p);
            }
            else if (j > a) {
                int cost_left = c - (j - a) / x;

                if (a - cost_left >= 0) {
                    dp[i + 1][a - cost_left] =
                        max(dp[i + 1][a - cost_left], dp[i][j] + p);
                }
            }
            else if (j <= a && j - c >= 0) {
                dp[i + 1][j - c] =
                    max(dp[i + 1][j - c], dp[i][j] + p);
            }
        }
    }

    cout << *max_element(dp[n + 1], dp[n + 1] + a + b + 1);
}