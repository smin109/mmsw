#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N, cnt = 1; cin >> N;
    stack < int > st;
    while(N --){
        int a; cin >> a;

        if(a == cnt) cnt++;
        else st.push(a);

        while(!st.empty() && st.top() == cnt){
            st.pop();
            cnt++;
        }
    }

    if(st.empty()) cout << "Nice";
    else cout << "Sad";
    return 0;
}