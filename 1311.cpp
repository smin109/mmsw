#include<bits/stdc++.h>
using namespace std;

int n; 
int arr[21][21];
int vi[21][1 << 20];

int dp(int ind, int mas){
    if(ind == n) return 0;

    int& ret = vi[ind][mas];
    if(ret != -1) return ret;

    ret = INT_MAX;
    for(int i = 0; i < n; i++){
        if((mas & (1 << i)) != 0) continue;
        ret = min(ret, arr[i][ind] + dp(ind + 1, mas | (1 << i)));
    }

    return ret;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cin >> n;

    memset(vi, -1, sizeof(vi));

    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> arr[i][j];

    cout << dp(0, 0);

    return 0;
}