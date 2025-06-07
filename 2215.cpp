#include<bits/stdc++.h>
using namespace std;
using pii = pair < int, int >;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N, P;
    cin >> N >> P;
    vector < pii > req(P);
    for(int i{0}; i < P; i++) cin >> req[i].first >> req[i].second;

    int ans{N};
    vector < pii > intervals;
    intervals.reserve(P);
    
    vector < int > pos(N + 1);
    for (int remove_edge{1}; remove_edge <= N; remove_edge++) {
        int start_node{remove_edge % N + 1};
        for (int j{1}; j <= N; j++) pos[j] = (j - start_node + N) % N + 1;

        intervals.clear();
        for (auto [u, v] : req) {
            int pu{pos[u]}, pv{pos[v]};
            if (pu == pv) continue;
            int l = min(pu, pv), r = max(pu, pv);
            intervals.emplace_back(l, r);
        }
        if (intervals.empty()) {
            ans = 0;
            break;
        }
        sort(intervals.begin(), intervals.end());
        int covered{0};
        int cur_end{0};
        for (auto [l, r] : intervals) {
            if (r <= cur_end) continue;
            if (l > cur_end) {
                covered += (r - l);
                cur_end = r;
            } else {
                covered += (r - cur_end);
                cur_end = r;
            }
        }
        ans = min(ans, covered);
    }

    cout << ans << '\n';
    return 0;
}
