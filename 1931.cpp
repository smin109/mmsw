#include<bits/stdc++.h>
using namespace std;

int value[10];

int main()
{
	int N, en, be; cin >> N;

	vector<pair<int, int>> sche;


	for (int i = 0; i < N; i++)
	{
		cin >> be >> en;
		sche.push_back({en, be});
	}
	
	sort(sche.begin(), sche.end());
	
	int t = sche[0].first;
	int cnt = 1;
	for (int i = 1; i < N; i++) 
	{
		if (t <= sche[i].second )
		{
			cnt++;
			t = sche[i].first;
		}
	}

	cout << cnt;
}