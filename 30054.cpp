#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector < ll > t1(N), t2(N);
    for (int i{0}; i < N; i++) cin >> t1[i] >> t2[i];

    vector < pair < ll,int > > ariv;
    ariv.reserve(N);
    for (int i{0}; i < N; i++) ariv.emplace_back(t2[i], i);
    
    sort(ariv.begin(), ariv.end());

    unordered_map < ll, vector < int > > reserveMap;
    reserveMap.reserve(N);

    for (int i{0}; i < N; i++) reserveMap[t1[i]].push_back(i);
    
    vector < ll > reserveTimes;
    reserveTimes.reserve(reserveMap.size());
    for (auto &kv : reserveMap) reserveTimes.push_back(kv.first);
    sort(reserveTimes.begin(), reserveTimes.end());

    vector < bool > seated(N,false);
    queue < int > waitQ;
    int seatedCnt{0};
    ll maxWait{0}, cur{0};
    int arrIdx{0}, R{reserveTimes.size()}, rPtr{0};
    const ll INF = LLONG_MAX / 4;

    while (seatedCnt < N) {
        while (arrIdx < N && ariv[arrIdx].first <= cur) {
            waitQ.push(ariv[arrIdx].second);
            arrIdx++;
        }

        int cand{-1};
        auto it = reserveMap.find(cur);
        if (it != reserveMap.end()) {
            for (int idx : it -> second) {
                if (!seated[idx] && t2[idx] <= cur) {
                    cand = idx;
                    break;
                }
            }
        }

        if (cand == -1) {
            while (!waitQ.empty() && seated[waitQ.front()]) {
                waitQ.pop();
            }
            if (!waitQ.empty()) {
                cand = waitQ.front();
                waitQ.pop();
            }
        }

        if (cand != -1) {
            seated[cand] = true;
            seatedCnt++;
            maxWait = max(maxWait, cur - t2[cand]);
            cur++;
        } else {
            ll nextArr = (arrIdx < N ? ariv[arrIdx].first : INF);
            while(rPtr < R && reserveTimes[rPtr] <= cur) rPtr++;
            ll nextRes = (rPtr < R ? reserveTimes[rPtr] : INF);
            ll nxt = min(nextArr, nextRes);
            if (nxt == INF) {
                cur++;
            } else {
                cur = nxt;
            }
        }
    }

    cout << maxWait << "\n";
    return 0;
}
