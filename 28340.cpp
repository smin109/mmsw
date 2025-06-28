#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N, K; cin >> N >> K;
        vector < ll > C(N);
        for (int i{0}; i < N; i++) cin >> C[i];

        int m{K - 1};
        if (m > 0) {
            int r{(N - 1) % m};
            int d{(r == 0 ? 0 : m - r)};
            C.insert(C.end(), d, 0LL);
        }

        priority_queue < ll, vector < ll >, greater < ll > > pq(C.begin(), C.end());

        ll cost{0};
        while (pq.size() > 1) {
            ll s{0};
            for (int i{0}; i < K; i++) {
                s += pq.top();
                pq.pop();
            }
            cost += s;
            pq.push(s);
        }

        cout << cost << endl;
    }
    
    return 0;
}
