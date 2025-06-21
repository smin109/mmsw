#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N, K; cin >> N >> K;
    vector < ll > E(N + 1), prefix(N + 1, 0), f(N + 1, 0), dp0(N + 1, 0);
    for (int i{1}; i <= N; i++) {
        cin >> E[i];
        prefix[i] = prefix[i - 1] + E[i];
    }

    deque < int > dq;
    dp0[0] = 0;
    f[0] = 0;
    dq.push_back(0);

    for (int i{1}; i <= N; i++) {
        dp0[i] = f[i - 1];
        while(!dq.empty() && dq.front() < i - K) dq.pop_front();
        ll bestA0 = dp0[dq.front()] - prefix[dq.front()];
        f[i] = max(dp0[i], prefix[i] + bestA0);
        ll A0_i = dp0[i] - prefix[i];
        while (!dq.empty() && (dp0[dq.back()] - prefix[dq.back()]) <= A0_i) dq.pop_back();
        dq.push_back(i);
    }

    cout << f[N] << endl;
    return 0;
}
