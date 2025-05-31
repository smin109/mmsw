#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    const int INF = 1e9;
    int n, t, m, s, e;
    cin >> n >> t >> m >> s >> e;

    vector < vector < int > > arr(t + 1, vector < int >(n, INF));
    arr[0][s] = 0;

    for (int j{0}; j < t; ++j) {
        arr[j + 1] = arr[j];

        for (int i{0}, x, y, w; i < m; ++i) {
            cin >> x >> y >> w;

            arr[j + 1][y] = min(arr[j + 1][y], arr[j][x] + w);
            arr[j + 1][x] = min(arr[j + 1][x], arr[j][y] + w);
        }
    }

    cout << ((arr[t][e] < INF) ? arr[t][e] : -1);
    return 0;
}
