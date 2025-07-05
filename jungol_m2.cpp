#include<bits/stdc++.h>
using namespace std;
const int INF{1e9};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    string A, B; cin >> A >> B;
    int p1, p3, p5, ppair; cin >> p1 >> p3 >> p5 >> ppair;

    vector < pair < int,int > > indiv = {
        {0, 0},
        {1, p1},
        {3, p3},
        {5, p5}
    };

    vector < pair < int, int > > pairs = {
        {0, 0},
        {4, ppair}
    };

    const int MAXR{5};
    vector < vector < int > > dp(MAXR + 1, vector < int >(MAXR + 1, INF));
    dp[0][0] = 0;

    for (int i[0]; i < N; i++) {
        int needA{A[i] - '0'};
        int needB{B[i] - '0'};
        vector < vector < int > > ndp(MAXR + 1, vector < int >(MAXR + 1, INF));

        for (int rA{0}; rA <= MAXR; rA++) {
            for (int rB{0}; rB <= MAXR; rB++) {
                int base{dp[rA][rB]};
                if (base == INF) continue;

                for (auto &ta : indiv) {
                    auto [dA, cA] = ta;
                    for (auto &tb : indiv) {
                        auto [dB, cB] = tb;
                        for (auto &tp : pairs) {
                            auto [dP, cP] = tp;

                            int cost{base + cA + cB + cP};
                            int coverA{max({rA, dA, dP})};
                            int coverB{max({rB, dB, dP})};
                            if (needA && coverA == 0) continue;
                            if (needB && coverB == 0) continue;

                            int nrA{max(coverA - 1, 0)};
                            int nrB{max(coverB - 1, 0)};
                            ndp[nrA][nrB] = min(ndp[nrA][nrB], cost);
                        }
                    }
                }
            }
        }

        dp.swap(ndp);
    }

    int ans{INF};
    for (int rA{0}; rA <= MAXR; rA++) for (int rB{0}; rB <= MAXR; rB++) ans = min(ans, dp[rA][rB]);

    cout << ans << "\n";

    return 0;
}
