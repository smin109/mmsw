#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    string cur, goal; cin >> cur >> goal;
    
    static int dp[10001][10];

    for (int i{0}; i <= n; i++) for (int j{0}; j < 10; j++) dp[i][j] = INF;

    dp[0][0] = 0;

    for (int i{0}; i < n; i++) {
        for (int j{0}; j < 10; j++) {
            if (dp[i][j] == INF) continue;

            int now{((cur[i] - '0') + j) % 10};
            int ta{goal[i] - '0'};

            int l{(ta - now + 10) % 10};
            int nl{(j + l) % 10};
            dp[i + 1][nl] = min(dp[i + 1][nl], dp[i][j] + l);

            int r{(now - ta + 10) % 10};
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + r);
        }
    }

    int ans{INF};
    for (int j{0}; j < 10; j++) ans = min(ans, dp[n][j]);

    cout << ans;
    return 0;
}