#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1'000'000'007LL;

struct BIT {
    int n; vector < ll > t;
    BIT(int n = 0): n (n), t (n + 1, 0) {}
    void reset(int n_) { n = n_; t.assign(n + 1, 0); }
    void add(int i, ll v) { for (; i <= n; i += i & -i) t[i] = (t[i] + v); }
    ll sum(int i) { ll s{0}; for (; i > 0; i-= i & -i) s += t[i]; return s;}
};

struct P {
    ll x, y; int yi, id;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n; cin >> n;

    vector < P > a(n);
    vector < ll > ys; ys.reserve(n);

    for (int i{0}; i < n; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].id = i;
        ys.push_back(a[i].y);
    }

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    auto getY = [&](ll y){ return int(lower_bound(ys.begin(), ys.end(), y) - ys.begin()) + 1; };

    for (int i{0}; i < n; i++) a[i].yi = getY(a[i].y);

    sort(a.begin(), a.end(), [](const P& a, const P& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    vector < ll > L(n, 0), R(n, 0);

    {
        BIT bit((int)ys.size());
        ll seen{0};

        for (int i{0}; i < n;) {
            int j{i};
            while (j < n && a[j].x == a[i].x) ++j;

            for (int k{i}; k < j; k++) {
                int yi{a[k].yi};
                ll leq{bit.sum(yi)};
                L[a[k].id] = seen - leq;
            }

            for (int k{i}; k < j; k++) {
                bit.add(a[k].yi, 1);
                ++seen;
            }
            i = j;
        }
    }


    {
        BIT bit((int)ys.size());
        ll seen{0};
        for (int i{n - 1}; i >= 0; ) {
            int j{i};
            while (j >= 0 && a[j].x == a[i].x) --j;

            for (int k{i}; k > j; --k) {
                int yi{a[k].yi};
                ll leq{bit.sum(yi)};
                R[a[k].id] = seen - leq;
            }
            
            for (int k{i}; k > j; --k) {
                bit.add(a[k].yi, 1);
                ++seen;
            }

            i = j;
        }
    }

    ll ans{0};

    for (int i{0}; i < n; i++) { ans = (ans + (L[i] % MOD) * (R[i] % MOD)) % MOD; }
    cout << ans % MOD;

    return 0;
}