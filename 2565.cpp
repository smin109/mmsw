#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;

    vector < vector < int > > v;

    for(int i = 0; i < n; i++){
        int a, b; cin >> a >> b;
        v.push_back({a, b});
    }

    sort(v.begin(), v.end());

    int ans = 0;
    int dp[101];

    for(int i = 0; i < n; i++){
        dp[i] = 1;
        for(int j = 0; j < i; j++) if(dp[j] + 1 > dp[i] && v[i][1] > v[j][1]) dp[i] = dp[j] + 1;

        ans = ans > dp[i] ? ans : dp[i];
    }

    cout << n - ans;
    return 0;
}