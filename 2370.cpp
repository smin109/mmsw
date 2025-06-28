#include<bits/stdc++.h>
using namespace std;

int n;
vector<pair<int,int>> point;
vector<int> v;
int mat[20001];
vector<int> ans;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n;

    for(int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        point.push_back({l, r});
        v.push_back(l);
        v.push_back(r);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    for(int i = 0; i < n; i++) {
        int l = lower_bound(v.begin(), v.end(), point[i].first) - v.begin();
        int r = lower_bound(v.begin(), v.end(), point[i].second) - v.begin();
        for(int j = l; j <= r; j++) mat[j] = i + 1;
    }

    for(int i = 0; i < 20000; i++) {
        if(mat[i] > 0) ans.push_back(mat[i]);
    }
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    cout << ans.size();
    return 0;
}
