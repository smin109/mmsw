#include <bits/stdc++.h>
using namespace std;

struct pair_hash {
    size_t operator() (const pair<double, double>& p) const {
        return hash<long long>()(llround(p.first * 1e6)) ^ hash<long long>()(llround(p.second * 1e6));
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> card(n);
    for (int i = 0; i < n; ++i) cin >> card[i];

    unordered_set<pair<double, double>, pair_hash> pair_set;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int dx = j - i;
            int dy = card[j] - card[i];
            if (dy % dx != 0) continue;
            int a = dy / dx;
            int b = card[j] - a * j;
            pair_set.insert({(double)a, (double)b});
        }
    }

    int ans = n;
    for (const auto& ab : pair_set) {
        int a = (int)ab.first;
        int b = (int)ab.second;
        int change = 0;
        for (int l = 0; l < n; ++l) {
            if (card[l] != a * l + b) ++change;
        }
        ans = min(ans, change);
    }
    cout << ans << '\n';
    return 0;
}
