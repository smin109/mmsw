#include<bits/stdc++.h>
using namespace std;

string num;
int n, m, k;
int ch[1000001][11];

int dfs(string now, int cnt) {
    if (cnt == k) return stoi(now);
    int &ret = ch[stoi(now)][cnt];
    if (ret != -1) return ret;

    for (int i{0}; i < m; i++) {
        for (int j{i + 1}; j < m; j++) {
            string tmp = now;
            swap(tmp[i], tmp[j]);
            if (tmp[0] == '0') continue;

            ret = max(ret, dfs(tmp, cnt + 1));
        }
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> num >> k;
    n = stoi(num);
    m = num.size();
    memset(ch, -1, sizeof(ch));

    if (m == 1 || (m == 2 && num[1] == '0')) cout << -1;
    else cout << dfs(num, 0);

    return 0;
}