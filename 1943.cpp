#include<bits/stdc++.h>
using namespace std;
#define LL long long

const int INF = 1e9;
const int MAX_M = 50001;
const int MAX_N = 101;
int N;
pair < int, int > Coin[MAX_N];
int DP[MAX_M];
vector < int > ans;

void sett(int Sum) {
	if (Sum % 2 == 1) {
		ans.push_back(0);
		return;
	}

	int Half{Sum / 2};
	for (int i{1}; i <= N; i++) for (int j{50000}; j >= 0; j--) if (j - Coin[i].first >= 0) if (DP[j - Coin[i].first]) for (int k{0}; k < Coin[i].second; k++) if (j + Coin[i].first * k < MAX_M) DP[j + Coin[i].first * k] = 1;

	if (DP[Half]) {
		ans.push_back(1);
		return;
	}

	ans.push_back(0);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); 
	
	for (int i{0}; i < 3; i++) {
		for (int j{0}; j < MAX_M; j++) DP[j] = 0;
		DP[0] = 1;
		
		cin >> N;
		int Sum{0};
		for (int j{1}; j <= N; j++) {
			cin >> Coin[j].first >> Coin[j].second;
			Sum += (Coin[j].first * Coin[j].second);
		}
		sett(Sum);
	}

	for (auto it : ans) cout << it << endl;

	return 0;
}
