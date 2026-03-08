// EXP Batch 1,2 and a few batch 3, 4

#include <bits/stdc++.h>
using namespace std;

#define ull unsigned long long
#define ll long long

const int MAXN = 5000;
int dp[MAXN + 1];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("EXP.INP", "r", stdin);
    freopen("EXP.OUT", "w", stdout);

    int t;
    cin >> t;

    for (int i = 1; i <= MAXN; i++) {
        dp[i] = i;
    }

    for (int n = 1; n <= MAXN; n++) {

        for (int i = 1; i <= n; i++) {
            if (n % i == 0) {
                int j = n / i;
                dp[n] = min(dp[n], dp[i] + dp[j] + 2);
            }
        }

        for (int i = 1; i < n; i++) {
            dp[n] = min(dp[n], dp[i] + dp[n - i] + 2);
        }
    }

    while (t--) {
        int n;
        cin >> n;
        cout << dp[n] << "\n";
    }

    return 0;
}