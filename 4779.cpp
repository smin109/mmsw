#include<bits/stdc++.h>
using namespace std;

void f(int n) {
    int s = pow(3, n - 1);

    if (n == 0) {
        cout << "-";
        return;
    }

    f(n - 1);

    for (int i = 0; i < s; i++) cout << " ";
    
    f(n - 1);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int n;
    
    while (cin >> n) {
        f(n);
        cout << '\n';
    }

    return 0;
}