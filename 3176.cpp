#include<bits/stdc++.h>
using namespace std;
const int INF = 100005;
const int LOG = 17;

vector < pair < int, int > > adj[INF];
int depth[INF], parent[INF][LOG];
int minEdge[INF][LOG], maxEdge[INF][LOG];

void dfs(int u, int p, int w) {
    parent[u][0] = p;
    minEdge[u][0] = w;
    maxEdge[u][0] = w;
    for (auto [v, len] : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u, len);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    for (int i{0}, A, B, C; i < N - 1; i++) {
        cin >> A >> B >> C;
        adj[A].push_back({B, C});
        adj[B].push_back({A, C});
    }

    memset(minEdge, 0x3f, sizeof(minEdge));
    memset(maxEdge, 0, sizeof(maxEdge));

    depth[1] = 0;
    dfs(1, 0, 0);

    for (int j{1}; j < LOG; j++) {
        for (int i{1}; i <= N; i++) {
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
            minEdge[i][j] = min(minEdge[i][j - 1], minEdge[parent[i][j - 1]][j - 1]);
            maxEdge[i][j] = max(maxEdge[i][j - 1], maxEdge[parent[i][j - 1]][j - 1]);
        }
    }

    int K; cin >> K;
    while (K--) {
        int u, v; cin >> u >> v;
        int minRes{INT_MAX}, maxRes{0};
        if (depth[u] < depth[v]) swap(u, v);

        for (int i{LOG - 1}; i >= 0; i--) {
            if (depth[u] - (1 << i) >= depth[v]) {
                minRes = min(minRes, minEdge[u][i]);
                maxRes = max(maxRes, maxEdge[u][i]);
                u = parent[u][i];
            }
        }

        if (u == v) {
            cout << minRes << ' ' << maxRes << '\n';
            continue;
        }

        for (int i{LOG - 1}; i >= 0; i--) {
            if (parent[u][i] != 0 && parent[u][i] != parent[v][i]) {
                minRes = min({minRes, minEdge[u][i], minEdge[v][i]});
                maxRes = max({maxRes, maxEdge[u][i], maxEdge[v][i]});
                u = parent[u][i];
                v = parent[v][i];
            }
        }

        minRes = min({minRes, minEdge[u][0], minEdge[v][0]});
        maxRes = max({maxRes, maxEdge[u][0], maxEdge[v][0]});
        cout << minRes << ' ' << maxRes << '\n';
    }
    return 0;
}
