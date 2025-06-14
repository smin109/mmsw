#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 300000;
int N;
vector < pair < int, int > > adj[MAXN + 1];
ll dsum;              
ll darr[MAXN + 1];      
int sz[MAXN + 1];           
ll ans[MAXN + 1];

void dfs1(int u, int p) {
    sz[u] = 1;
    for (auto [v, w] : adj[u]) {
        if (v == p) continue;
        darr[v] = darr[u] + w;
        dfs1(v, u);
        sz[u] += sz[v];
    }
    dsum += darr[u];
}

void dfs2(int u, int p) {
    for (auto [v, w] : adj[u]) {
        if (v == p) continue;
        ans[v] = ans[u] + (ll)(N - 2LL * sz[v]) * w;
        dfs2(v, u);
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> N;
    for (int i{1}, u, v, d; i < N; i++) {
        cin >> u >> v >> d;
        adj[u].emplace_back(v, d);
        adj[v].emplace_back(u, d);
    }

    darr[1] = 0;
    dsum = 0;
    dfs1(1, 0);

    ans[1] = dsum;

    dfs2(1, 0);

    ll* p = &ans[1];
    for (int i = {1}; i <= N; i++) cout << *p++ << '\n';
    
    return 0;
}
