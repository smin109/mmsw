#include<bits/stdc++.h>
using namespace std;

int find(int x, vector < int > &p) {
    return p[x] == x ? x : p[x] = find(p[x], p);
}

void unite(int a, int b, vector < int > &p, vector < unordered_map < int, int > > &cnt) {
    a = find(a, p); b = find(b, p);
    if (a == b) return;
    if (cnt[a].size() < cnt[b].size()) swap(a, b);
    for (auto &x : cnt[b]) cnt[a][x.first] += x.second;
    p[b] = a;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n, q; cin >> n >> q;
    vector < int > pa(n + 1), co(n + 1), dsu(n + 1);
    vector < unordered_map < int, int > > cnt(n + 1);
    vector < pair < int, int > > qry;
    vector < int > res;

    pa[1] = 1;
    for (int i{2}; i <= n; i++) cin >> pa[i];
    for (int i{1}; i <= n; i++) cin >> co[i];

    int total = n + q - 1;
    vector < int > type(total), node(total);
    for (int i{0}; i < total; i++) cin >> type[i] >> node[i];

    for (int i{1}; i <= n; i++) dsu[i] = i, cnt[i][co[i]]++;

    for (int i{total - 1}; i >= 0; i--) {
        int t{type[i]}, a{node[i]};
        if (t == 2) {
            int r = find(a, dsu);
            res.push_back(cnt[r].size());
        } else {
            unite(a, pa[a], dsu, cnt);
        }
    }

    for (int i = res.size() - 1; i >= 0; i--) cout << res[i] << '\n';

    return 0;
}
