#include<bits/stdc++.h>
using namespace std;
const int MAX = 12;

int n, m;
int arr[MAX][MAX];
int mp[MAX][MAX];
bool check[MAX][MAX];

struct coor {
    int y;
    int x;
    int num;
};
queue <coor> q;
queue <coor> bq;

int gNum = 1;

bool inside(int y, int x) {
    return y >= 0 && y < n && x >= 0 && x < m;
}
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };

struct bridge {
    int a;
    int b;
    int c;
};
vector <bridge> v;

bool cmp(const bridge & a, const bridge & b) {
    return a.c < b.c;
}

vector<int> p;

void bfs() {
    while (!q.empty()) {
        int y = q.front().y;
        int x = q.front().x;
        int num = q.front().num;
        q.pop();
        
        int ny, nx;
        for (int i = 0; i < sizeof(dy)/sizeof(dy[0]); i++) {
            ny = y + dy[i];
            nx = x + dx[i];
            if (inside(ny, nx) && check[ny][nx] == 0 && arr[ny][nx] == 1) {
                check[ny][nx] = 1;
                mp[ny][nx] = num;
                q.push({ ny,nx,num });
                bq.push({ ny,nx,num });
            }
        }
    }
}

int find(int x) {
    if (p[x] == x) return x;
    else return p[x] = find(p[x]);
}
void Union(int a, int b) {
    a = find(a);
    b = find(b);
    p[a] = b;
}
bool sp(int a, int b) {
    return find(a) == find(b);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    memset(check, 0, sizeof(check));
    cin >> n >> m;
    p.resize(n * m + 1);
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> arr[i][j];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == 1 && check[i][j] == 0) {
                check[i][j] = 1;
                mp[i][j] = gNum;
                q.push({ i,j,gNum });
                bq.push({ i,j,gNum });
                bfs();
                gNum++;
            }
        }
    }

    memset(check, 0, sizeof(check));
    while (!bq.empty()) {
        int y = bq.front().y;
        int x = bq.front().x;
        int num = bq.front().num;
        bq.pop();

        int ny, nx;
        for (int i = 0; i < sizeof(dy)/sizeof(dy[0]); i++) {
            int s = 1;
            int cnt = 1;
            while (true) {
                ny = y + dy[i] * s;
                nx = x + dx[i] * s;
                if (!inside(ny, nx)) break;
                if (mp[ny][nx] == num) break;
                if (mp[ny][nx] != 0 && mp[ny][nx] != num) {
                    if (cnt - 1 >= 2) v.push_back({ num, mp[ny][nx], cnt - 1 });
                    break;
                }
                s++;
                cnt++;
            }
        }
    }

    for (int i = 1; i <= n * m; i++) p[i] = i;
    sort(v.begin(), v.end(), cmp);

    int ans = 0;
    vector <int> c[7];
    vector<bool> check2(n * m + 1, false);
    queue <int> lq;
    int m = 0;
    for (int i = 0; i < v.size(); i++) {
        if (!sp(v[i].a, v[i].b)) {
            Union(v[i].a, v[i].b);
            ans += v[i].c;
            c[v[i].a].push_back(v[i].b);
            c[v[i].b].push_back(v[i].a);
            if (m == 0) m = v[i].a;
        }
    }

    lq.push(m);
    while (!lq.empty()) {
        int num = lq.front();
        lq.pop();
        check2[num] = true;
        for (int i = 0; i < c[num].size(); i++) {
            if (!check2[c[num][i]]) {
                check2[c[num][i]] = true;
                lq.push(c[num][i]);
            }
        }
    }

    bool flag = false;
    for (int i = 1; i < gNum; i++) {
        if (!check2[i]) flag = true;
    }

    cout << (flag ? -1 : ans) << "\n";
    return 0;
}