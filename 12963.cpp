#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
const int MAX_SIZE = 2001;

int parent[MAX_SIZE];

int find(int x) { return x == parent[x] ? x : parent[x] = find(parent[x]); }

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int nodeCount, edgeCount;
    int from[MAX_SIZE], to[MAX_SIZE], powerOfThree[MAX_SIZE];

    cin >> nodeCount >> edgeCount;
    for (int i{0}; i < edgeCount; i++) cin >> from[i] >> to[i];

    iota(parent, parent + nodeCount, 0);

    powerOfThree[0] = 1;
    for (int i{1}; i < edgeCount; i++) powerOfThree[i] = powerOfThree[i - 1] * 3ll % MOD;

    int answer{0};
    for (int i{edgeCount - 1}; i >= 0; i--) {
        int uRoot = find(from[i]);
        int vRoot = find(to[i]);
        int startRoot = find(0);
        int endRoot = find(nodeCount - 1);

        if (min(uRoot, vRoot) == min(startRoot, endRoot) &&
            max(uRoot, vRoot) == max(startRoot, endRoot)) {
            answer = (answer + powerOfThree[i]) % MOD;
        } else {
            parent[uRoot] = vRoot;
        }
    }

    cout << answer;

    return 0;
}
