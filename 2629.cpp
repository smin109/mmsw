#include<bits/stdc++.h>
using namespace std;

int arr[31];
int n; 
int ch[31][15001];

void dp(int i, int weight){
    if(i > n || ch[i][weight]) return;
    ch[i][weight] = 1;
    dp(i + 1, weight + arr[i]);
    dp(i + 1, abs(weight - arr[i]));
    dp(i + 1, weight);
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    
    memset(ch, 0, sizeof(ch));
    cin >> n;

    for(int i = 0; i < n; i++) cin >> arr[i];

    dp(0, 0);
    
    int t; cin >> t;

    while(t--){
        int a; cin >> a;

        if(a > 15000) cout << "N ";
        else if(ch[n][a]) cout << "Y ";
        else cout << "N ";
    }

    return 0;
}