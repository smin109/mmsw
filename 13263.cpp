#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    ll m, c;
};

bool bad(const Line &l1, const Line &l2, const Line &l3) {
    __int128 lhs = (__int128)(l2.c - l1.c) * (l1.m - l3.m);
    __int128 rhs = (__int128)(l3.c - l1.c) * (l1.m - l2.m);
    return lhs >= rhs;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;
    vector < ll > a(n + 1), b(n + 1), D(n + 1);
    for (int i{1}; i <= n; i++) cin >> a[i];
    for (int i{1}; i <= n; i++) cin >> b[i];

    deque < Line > dq;
    dq.push_back({b[1], 0});

    for (int i{2}; i <= n; i++) {
        ll x = a[i];
        while (dq.size() >= 2) {
            ll y1 = dq[0].m * x + dq[0].c;
            ll y2 = dq[1].m * x + dq[1].c;
            if (y2 <= y1) dq.pop_front();
            else break;
        }
        D[i] = dq.front().m * x + dq.front().c;
        Line nw = {b[i], D[i]};
        while (dq.size() >= 2 && bad(dq[dq.size()-2], dq[dq.size()-1], nw)) {
            dq.pop_back();
        }
        dq.push_back(nw);
    }

    cout << D[n] << "\n";
    return 0;
}
