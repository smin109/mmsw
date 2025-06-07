#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)1e18;

struct Edge { int u, v; ll w; };

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector < Edge > edges;
    edges.reserve(M + N);

    for (int i{0}, a, type, b; i < M; i++) {
        ll x;
        cin >> a >> type >> b >> x;
        if (!type) {
            edges.push_back({b, a, x});
        } else {
            edges.push_back({a, b, -x});
        }
    }

    for (int i{1}; i <= N; i++) edges.push_back({0, i, 0});

    int V{N + 1};
    vector < ll > dist(V, INF);
    dist[0] = 0;

    bool updated{false};
    for (int iter{0}; iter <= V; iter++) {
        updated = false;
        for (auto &e : edges) {
            if (dist[e.u] != INF && dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                updated = true;
            }
        }
        if (iter == V && updated) {
            cout << -1;
            return 0;
        }
        if (!updated) break;
    }

    ll dmin{INF}, dmax{-INF};
    for (int i{1}; i <= N; i++) {
        dmin = min(dmin, dist[i]);
        dmax = max(dmax, dist[i]);
    }

    if (dmax - dmin > 1000000LL - 1) {
        cout << -1;
        return 0;
    }

    for (int i{1}; i <= N; i++) {
        ll wi = dist[i] - dmin + 1;
        cout << wi << '\n';
    }

    return 0;
}
