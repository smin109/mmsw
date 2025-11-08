#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX = 19;
ll n, k;
string N;
ll dp[MAX + 1][1 << 10][2][2], ten[MAX];

ll solve(int pos, int used, bool isBig, bool leading0) {
    ll &ret = dp[pos][used][isBig][leading0];
    if (ret != -1) return ret;

    if (pos == MAX) {
        if (!isBig) return ret = -2;
        int cnt{0};
        for (int i{0}; i < 10; i++) cnt += (used & (1 << i)) > 0;
        if (cnt != k) return ret = -2;
        return ret = 0;
    }

    ret = 0;

    if (leading0 && N[pos] == 0) {
        ll next(solve(pos + 1, used, isBig, leading0));
        if (next >= 0) return ret = next;
    }

    for (int i{(isBig ? 0 : N[pos])}; i < 10; i++) {
        if (leading0 && i == 0) continue;
        ll next{solve(pos + 1, used | (1 << i), isBig || (i > N[pos]), leading0 && !i)};
        if (next >= 0) return ret = next + ten[pos]*i;
    }

    return ret = -2;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    
    cin >> n >> k;

    N = to_string(n - 1);
    
    while (N.size() < MAX) N = "0" + N;

    for(int i{0}; i < MAX; i++) N[i] -= '0';
    ten[MAX - 1] = 1;
    for(int i{MAX - 2}; i >= 0; i--) ten[i] = ten[i + 1] * 10;
    memset(dp, -1, sizeof(dp));
    cout << solve(0, 0, 0, 1);

    return 0;
}
