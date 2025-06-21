#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)4e18;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N, M, C, D; cin >> N >> M >> C >> D;
    vector < int > b(N);
    for (int i{0}; i < N; i++) cin >> b[i];

    unordered_map < int, int > r2idx;
    vector < vector < int > > ks;
    ks.reserve(min(M, C));
    for (int k{1}; k <= M; k++) {
        int r{k % C};
        auto it = r2idx.find(r);
        if (it == r2idx.end()) {
            int idx{ks.size()};
            r2idx[r] = idx;
            ks.push_back({});
            ks[idx].reserve((M / C) + 1);
            it = r2idx.find(r);
        }
        ks[it -> second].push_back(k);
    }
    int G{ks.size()};
    int L{D / C};

    vector < vector < ll > > dp_prev(G), dp_cur(G);

    for (int g{0}; g < G; g++) {
        int m{ks[g].size()};
        dp_prev[g].resize(m);
        for (int i{0}; i < m; i++) dp_prev[g][i] = llabs(b[0] - ks[g][i]);
    }

    for (int t{1}; t < N; t++) {
        for (int g{0}; g < G; g++) {
            int m{ks[g].size()};
            auto &prev = dp_prev[g];
            auto &cur = dp_cur[g];
            cur.assign(m, INF);

            int arr_size{m + 2 * L};
            int W {2 * L + 1};
            deque < pair < ll, int > > dq;

            for (int i{0}; i < arr_size; i++) {
                ll val;
                if(i < L)              val = INF;
                else if(i < L + m)     val = prev[i - L];
                else                   val = INF;

                while(!dq.empty() && dq.back().first >= val) dq.pop_back();
                
                dq.emplace_back(val, i);

                if (dq.front().second <= i - W) dq.pop_front();

                if (i >= W - 1) {
                    int idx{i - (W - 1)};
                    ll best = dq.front().first;
                    cur[idx] = best + llabs(b[t] - ks[g][idx]);
                }
            }
        }
        dp_prev.swap(dp_cur);
    }

    ll min_penalty{INF};
    for (int g{0}; g < G; g++) for(ll v : dp_prev[g]) min_penalty = min(min_penalty, v);

    ll ans{ll(N) * M - min_penalty};
    cout << ans;

    return 0;
}
