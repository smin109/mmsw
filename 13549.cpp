#include<bits/stdc++.h>
using namespace std;
#define MA 100001

int main(){
    int N, K; cin >> N >> K;

    int vi[MA];
    memset(vi, -1, sizeof(vi));
    
    deque < int > dq;
    dq.push_back(N);
    vi[N] = 0;

    while(!dq.empty()){
        int pos_x = dq.front();
        dq.pop_front();

        if(pos_x == K){
            cout << vi[K];
            return 0;
        }

        if(pos_x * 2 < MA &&(vi[pos_x * 2] == -1 || vi[pos_x * 2] > vi[pos_x])){
            dq.push_front(pos_x * 2);
            vi[pos_x * 2] = vi[pos_x];
        }

        if(pos_x + 1 < MA && vi[pos_x + 1] == -1){
            dq.push_back(pos_x + 1);
            vi[pos_x + 1] = vi[pos_x] + 1;
        }

        if(pos_x - 1 >= 0 && vi[pos_x - 1] == -1){
            dq.push_back(pos_x - 1);
            vi[pos_x - 1] = vi[pos_x] + 1;
        }
    }

    return 0;
}
