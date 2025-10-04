#include <bits/stdc++.h>
using namespace std;
const int INF = INT_MAX;

vector < int > dijk(int start, int n, vector < vector < pair < int, int > > >& v){
    vector < int > di(n + 1, INF);
    priority_queue < pair < int, int >, vector < pair < int, int > >, greater < pair < int, int > > > pq;
    di[start] = 0;
    pq.push({0, start});

    while(!pq.empty()){
        auto [d, u] = pq.top(); pq.pop();

        if(d > di[u]) continue;

        for(auto& edge : v[u]){
            auto [v, weight] = edge;

            if(di[u] + weight < di[v]){
                di[v] = di[u] + weight;
                pq.push({di[v], v});
            }
        }
    }

    return di;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int T; cin >> T;

    while(T--){
        int n, m, t; cin >> n >> m >> t;
        int s, g, h; cin >> s >> g >> h;

        vector < vector < pair < int, int > > > v(n + 1);

        for(int i = 0; i < m; i++){
            int a, b, c; cin >> a >> b >> c;
            v[a].push_back({b, c}); v[b].push_back({a, c});
        }

        vector < int > candi(t);
        for(int i = 0; i < t; i++) cin >> candi[i];

        vector < int > di_s = dijk(s, n, v);
        vector < int > di_g = dijk(g, n, v);
        vector < int > di_h = dijk(h, n, v);

        vector < int > result;
        for(int candidate : candi){
            int di_via_g_h = di_s[g] + di_g[h] + di_h[candidate];
            int di_via_h_g = di_s[h] + di_h[g] + di_g[candidate];
            int direct_di = di_s[candidate];

            if(direct_di == min(di_via_g_h, di_via_h_g)) result.push_back(candidate);
        }

        sort(result.begin(), result.end());

        for(int res : result) cout << res << ' ';
        cout << '\n';
    }

    return 0;
}