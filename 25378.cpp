#include<bits/stdc++.h>
using namespace std;

void update(int num, int cnt, unordered_map < int, int >& mp) {
    if (mp.find(num) == mp.end()) mp[num] = cnt;
    else mp[num] = min(mp[num], cnt);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int N; cin >> N;
    vector < int > arr(N);
    for (int i{0}; i < N; i++) cin >> arr[i];

    unordered_map < int, int > mp;
    mp[arr[0]] = 0;
    for (int i{0}; i < N - 1; i++) {
        unordered_map < int, int > nextMap;
        for (auto& p : mp) {
            int A{p.first}, v{p.second};
            int B{arr[i + 1]};
            if (A == 0) {
                update(B, v, nextMap);
            } else {
                if (A < B) {
                    update(B - A, v + 1, nextMap);
                    update(B, v + 1, nextMap);
                } else if (A > B) {
                    update(B, v + 1, nextMap);
                } else {
                    update(0, v + 1, nextMap);
                }
            }
        }
        mp = move(nextMap);
    }
    
    int answer{INT_MAX};
    
    for (auto& p : mp) {
        int num{p.first}, value{(num == 0 ? p.second : p.second + 1)};
        answer = min(answer, value);
    }

    cout << answer;
    return 0;
}
