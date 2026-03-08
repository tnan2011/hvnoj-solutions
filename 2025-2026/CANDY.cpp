// CANDY FULL

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("CANDY.INP", "r", stdin);
    freopen("CANDY.INP", "w", stdout);

    int n, f, g;
    cin >> n >> f >> g;

    vector<int> e(n), w(n), c(n);

    for (int &x : e) cin >> x;
    for (int &x : w) cin >> x;
    for (int &x : c) cin >> x;

    double ans = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        int cost = 0;
        int E = 0;
        int W = 0;

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                cost += c[i];
                E += e[i];
                W += w[i];
            }
        }

        if (cost <= f) {
            double T = 0;

            if (W + g > 0) {
                T = 1.0 * E / (W + g);
            }

            ans = max(ans, T);
        }
    }

    cout << fixed << setprecision(10) << ans << "\n";
}