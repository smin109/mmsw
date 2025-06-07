#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n;
ll dp[24];

int pos(int p, int d1, int c1, int d2, int c2) {
    ll x{n};
    int t1{0}, t2{0};
    for (int i{0}; x; i++) {
        if (i >= p && x % 10 == d1) t1++;
        if (i >= p && x % 10 == d2) t2++;
        x /= 10;
    }
    t1 = c1 < t1 ? 0 : c1 - t1;
    t2 = c2 < t2 ? 0 : c2 - t2;
    return (t1 + t2 <= p);
}

int main() {
    int d1, c1, d2, c2, p{0};
    cin >> n >> d1 >> c1 >> d2 >> c2;

    dp[0] = 1;
    for (int i{1}; i <= 16; i++) dp[i] = dp[i - 1] * 10;

    while (p >= 0) {
        if (pos(p, d1, c1, d2, c2)) p--;
        else {
            n += dp[p];
            if (n / dp[p] % 10 == 0) p++;
        }
    }
    cout << n;
    return 0;
}
