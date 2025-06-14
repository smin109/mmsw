#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N, D; cin >> N >> D;
    vector < ll > K(N + 1), dp(N + 1);
    for (int i{1}; i <= N; i++) cin >> K[i];

    deque < pair < int, ll > > dq;
    ll ans = LLONG_MIN;

    for (int i{1}; i <= N; i++) {
        while (!dq.empty() && dq.front().first < i - D) dq.pop_front();

        if (dq.empty()) dp[i] = K[i];
        else dp[i] = K[i] + max(0LL, dq.front().second);

        while (!dq.empty() && dq.back().second <= dp[i]) dq.pop_back();

        dq.emplace_back(i, dp[i]);
        ans = max(ans, dp[i]);
    }
    cout << ans;
    
    return 0;
}
