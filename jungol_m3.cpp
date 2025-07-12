#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Fenwick {
    int n;
    vector<ll> t;
    Fenwick(int _n): n(_n), t(n+1, 0) {}
    void add(int i, ll v) {
        for (; i <= n; i += i & -i) t[i] += v;
    }
    ll sum(int i) const {
        ll s = 0;
        for (; i > 0; i -= i & -i) s += t[i];
        return s;
    }
    ll total() const { return sum(n); }
    int lower_bound(ll x) const {
        int pos = 0;
        ll cur = 0;
        int L = 1 << (31 - __builtin_clz(n));
        for (int step = L; step > 0; step >>= 1) {
            if (pos + step <= n && cur + t[pos + step] < x) {
                cur += t[pos + step];
                pos += step;
            }
        }
        return pos + 1;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<ll> D(N);
    for (int i = 0; i < N; i++) {
        cin >> D[i];
    }

    vector<ll> comp = D;
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    int M = comp.size();

    vector<int> idx(N);
    for (int i = 0; i < N; i++) {
        idx[i] = int(lower_bound(comp.begin(), comp.end(), D[i]) - comp.begin()) + 1;
    }

    vector<vector<pair<ll,int>>> queries(N+1);
    for (int j = 0; j < Q; j++) {
        int X; ll P;
        cin >> X >> P;
        queries[X].push_back({P, j});
    }

    vector<ll> ans(Q, -1);
    Fenwick BIT_cnt(M), BIT_sum(M);
    int cnt_added = 0;

    for (int x = 1; x <= N; x++) {
        BIT_cnt.add(idx[x-1], 1);
        BIT_sum.add(idx[x-1], D[x-1]);
        cnt_added++;

        for (auto &q : queries[x]) {
            ll P = q.first;
            int qi = q.second;

            ll total = BIT_sum.total();
            if (total < P) {
                ans[qi] = -1;
                continue;
            }

            ll T = total - P;
            int k = BIT_sum.lower_bound(T + 1);
            ll val = comp[k-1];

            ll sum_le_k = BIT_sum.sum(k);
            ll cnt_le_k = BIT_cnt.sum(k);

            ll sum_strict = total - sum_le_k;
            ll cnt_strict = cnt_added - cnt_le_k;

            ll need = P - sum_strict;
            ll take_eq = (need <= 0 ? 0 : (need + val - 1) / val);

            ans[qi] = cnt_strict + take_eq;
        }
    }

    ostringstream out;
    for (int i = 0; i < Q; i++) {
        out << ans[i] << '\n';
    }
    cout << out.str();
    return 0;
}
