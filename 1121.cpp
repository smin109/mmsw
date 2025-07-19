#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(nullptr);

    int N; cin >> N;
    vector < int > a(N);
    for (int i{0}; i < N; i++) cin >> a[i];
    int K; cin >> K;
    if (N < K) {
        cout << 0;
        return 0;
    }

    sort(a.begin(), a.end());
    
    int M{a.back()};
    
    vector < vector < long long > > dp(K, vector < long long > (M + 1));
    dp[0][0] = 1;
    vector < vector < long long > > C(N + 1, vector < long long >(K + 1));
    for (int i{0}; i <= N; i++) {
        C[i][0] = 1;
        for (int j{1}; j <= min(i, K); j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    long long ans{0};
    int val{a[0]};
    for (int s{val}; s <= M; s++) dp[1][s] += dp[0][s - val];
    
    for (int i{1}; i < N; i++) {
        if (i >= K - 1) {
            long long total{C[i][K - 1]};
            int th{a[i]};
            long long sum{0};
            for (int s{0}; s <= th; s++) sum += dp[K-1][s];
            ans += total - sum;
        }
        val = a[i];
        for (int j{min(i + 1, K - 1)}; j >= 1; j--) for (int s {M}; s >= val; s--) dp[j][s] += dp[j - 1][s - val];
    }
    cout << ans;
    return 0;
}
