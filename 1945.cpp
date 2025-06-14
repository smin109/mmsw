#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<pair<double,int>> events;
    events.reserve(2 * N);

    for (int i = 0; i < N; i++) {
        double xbl, ybl, xtr, ytr;
        cin >> xbl >> ybl >> xtr >> ytr;
        double start = atan2(ybl, xtr);
        double end   = atan2(ytr, xbl);
        events.emplace_back(start, +1);
        events.emplace_back(end,   -1);
    }

    sort(events.begin(), events.end(), [](auto &a, auto &b) {
        if (a.first != b.first) 
            return a.first < b.first;
        return a.second > b.second;
    });

    int cnt = 0, answer = 0;
    for (auto &e : events) {
        cnt += e.second;
        answer = max(answer, cnt);
    }

    cout << answer << "\n";
    return 0;
}
