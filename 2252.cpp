#include<bits/stdc++.h>
using namespace std;

vector < int > front[32001];
int vi[32001] = {false,};

void DFS(int node){
	vi[node] = true;
	for(int i = 0; i < front[node].size(); i++) if(vi[front[node][i]] == false) DFS(front[node][i]);
	cout << node << " ";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

	int n, m; cin >> n >> m;

	for(int i = 0; i < m; i++){
		int a, b; cin >> a >> b;
		front[b].push_back(a);
	}

	for(int i = 1; i <= n; i++) if(vi[i] == false) DFS(i);

	return 0;
}