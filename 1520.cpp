#include<bits/stdc++.h>
using namespace std;

const int MA = 501;
const pair<int, int> direction[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
int M, N;
int ma[MA][MA];
int cache[MA][MA];

int DFS(int y, int x)
{
    if (y == M && x == N) return 1;

    if (cache[y][x] == -1) 
    {
        cache[y][x] = 0;

        for (int i = 0; i < 4; i++) 
        {
            int ny = y + direction[i].first;
            int nx = x + direction[i].second;

            if (ma[ny][nx] != 0 && ma[y][x] > ma[ny][nx]) 
                cache[y][x] += DFS(ny, nx);
        }
    }
    return cache[y][x];
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> M >> N;

    memset(cache, -1, sizeof(cache));
    
    for (int i = 1; i <= M; i++) for (int j = 1; j <= N; j++) cin >> ma[i][j];

    cout << DFS(1, 1);

    return 0;
}