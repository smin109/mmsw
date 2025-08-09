#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n, k;
    if (!(cin >> n >> k)) return 0;
    int m{n * 2};
    vector < int > v(n);
    for (int i{0}; i < n; i++) cin >> v[i];

    vector < int > r = v;
    reverse(r.begin(), r.end());

    vector < int > b(m);
    for (int i{0}; i < n; i++) b[i] = r[i];
    for (int i{0}; i < n; i++) b[i + n] = r[i];

    {
        vector < int > comp = b;
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()), comp.end());
        for (int& x : b) x = int(lower_bound(comp.begin(),comp.end(), x) - comp.begin()) + 1;
    }

    vector < int > sa(m), rn(m), tmp(m);

    for (int i{0}; i < m; i++) sa[i] = i, rn[i] = b[i];

    for (int k{1}; ; k <<= 1) {
        auto cmp = [&](int i, int j) {
            if (rn[i] != rn[j]) return rn[i] < rn[j];
            int ri{(i + k < m) ? rn[i + k] : -1}, rj{(j + k < m) ? rn[j + k] : -1};
            return ri < rj;
        };
        sort(sa.begin(), sa.end(), cmp);
        
        tmp[sa[0]] = 0;
        for (int i{1}; i < m; i++) tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        for (int i{0}; i < m; i++) rn[i] = tmp[i];
        if (rn[sa.back()] == m - 1) break;
    }

    int cnt{0}, st{-1};

    for (int p{0}; p < m; p++) {
        int s{sa[p]};
        if (s < n && s != 0) {
            cnt++;
            if (cnt == k) { st = s; break; }
        }
    }

    for (int i{0}; i < n; i++) {
        if (i) cout << ' ';
        cout << r[(st + i) % n];
    }

    return 0;
}