#include<bits/stdc++.h> 
using namespace std;
 
struct P{
    int r, c;
};
 
int R, C;
vector < string > Lake;
queue < P > sq, wq, tsq, twq;
int dr[]{1, -1, 0, 0}, dc[]{0, 0, 1, -1};
bool vi[1501][1501], found{false};
 
void sbfs() {
    while (!sq.empty()) {
        P now = sq.front();
        sq.pop();
        
        for (int i{0}; i < 4; i++) {
            int nr = now.r + dr[i];
            int nc = now.c + dc[i];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C || vi[nr][nc]) continue;
            
            vi[nr][nc] = true;
            if (Lake[nr][nc] == 'X') {
                tsq.push({nr, nc});
            } else if (Lake[nr][nc] == '.') {
                sq.push({nr, nc});
            } else if (Lake[nr][nc] == 'L') {
                found = true;
                break;
            }
        }
    }
}
 
void wbfs() {
    while (!wq.empty()) {
        P now = wq.front();
        wq.pop();
        
        for (int i{0}; i < 4; i++) {
            int nr = now.r + dr[i];
            int nc = now.c + dc[i];
            if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
            
            if (Lake[nr][nc] == 'X') {
                Lake[nr][nc] = '.';
                twq.push({nr, nc});
            }
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    
    string line;
    P swan;
    cin >> R >> C;
    for (int i{0}; i < R; i++) {
        cin >> line;
        Lake.push_back(line);
        for (int j{0}; j < C; j++) {
            if (line[j] != 'X') wq.push({i, j});
            if (line[j] == 'L') {
                swan.r = i;
                swan.c = j;
            }
            
        }
    }
    sq.push(swan);
    vi[swan.r][swan.c] = true;
    
    int day{0};
    
    while (!found) {
        sbfs();
        if (found) break;
        wbfs();
        
        sq = tsq;
        wq = twq;
        
        tsq = queue < P >();
        twq = queue < P >();
        
        day++;
    }
    
    cout << day;
    
    return 0;
}