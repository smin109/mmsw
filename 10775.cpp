#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int arr[100001];

int fi(int x) {
    if (x == arr[x]) return x;
    return arr[x] = fi(arr[x]);
}

void un(int a, int b) {
    a = fi(a); b = fi(b);

    if (a > b) swap(a, b);
    arr[b] = a;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n, m, ans{0}; cin >> n >> m;
    for (int i{0}; i <= n; i++) arr[i] = i;

    while (m--) {
        int a; cin >> a;
        a = fi(a); if (!a) break;
        un(a, a - 1);
        ans++;
    }
    cout << ans;

    return 0;
}