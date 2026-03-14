// BPHOTO FULL (btww i love fenwick)

#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick(int size) {
        n = size;
        bit.assign(n + 2, 0);
    }

    void update(int i, int v) {
        while (i <= n) {
            bit[i] += v;
            i += i & -i;
        }
    }

    int query(int i) {
        int res = 0;
        while (i > 0) {
            res += bit[i];
            i -= i & -i;
        }
        return res;
    }

    int query_range(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("BPHOTO.INP", "r", stdin);
    freopen("BPHOTO.INP", "w", stdout);

    int n;
    cin >> n;

    vector<int> h(n);
    for (int &x : h) cin >> x;

    vector<int> sorted = h;
    sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());

    unordered_map<int, int> compress;
    for (int i = 0; i < sorted.size(); i++) {
        compress[sorted[i]] = i + 1;
    }

    int maxRank = sorted.size();
    vector<int> l(n), r(n);

    Fenwick bit(maxRank);

    for (int i = 0; i < n; i++) {
        int rank = compress[h[i]];
        l[i] = bit.query_range(rank + 1, maxRank);
        bit.update(rank, 1);
    }

    bit = Fenwick(maxRank);

    for (int i = n - 1; i >= 0; i--) {
        int rank = compress[h[i]];
        r[i] = bit.query_range(rank + 1, maxRank);
        bit.update(rank, 1);
    }

    int result = 0;

    for (int i = 0; i < n; i++) {
        if (l[i] * 2 < r[i] || r[i] * 2 < l[i]) {
            result++;
        }
    }

    cout << result << "\n";

    return 0;
}
