#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;

    vector < int > app(n), mem(n);
    int sum = 0;

    for(int i = 0; i < n; i++) cin >> app[i];
    for(int i = 0; i < n; i++){
        cin >> mem[i];
        sum += mem[i];
    }

    vector < int > dp(sum + 1, 0);

    for(int i = 0; i < n; i++) for(int j = sum; j >= mem[i]; j--) dp[j] = max(dp[j], dp[j - mem[i]] + app[i]);

    for(int i = 0; i <= sum; i++){
        if(dp[i] >= m){
            cout << i;
            break;
        }
    }

    return 0;
}
