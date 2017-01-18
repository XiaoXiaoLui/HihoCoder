// include stdc++.h slows down compilation much.
//#include<bits/stdc++.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstring>

using namespace std;

#define USE_IOSTREAM \
{\
	ios::sync_with_stdio(false);\
	cin.tie(0);\
	cout.tie(0);\
}

#define pii pair<int, int>
#define mp make_pair

typedef long long ll;


const int N = 1010;
const ll MOD = 1e9 + 7;

ll dp[N][1 << 5];

void dfs(int bit, int cur, int next, ll *res, ll pre)
{
	while (bit >= 0 && cur >> bit & 1)
	{
		bit--;
	}
	if (bit < 0)
	{
		res[next] = (res[next] + pre) % MOD;
		return;
	}
	
	dfs(bit - 1, cur | 1 << bit, next | 1 << bit, res, pre);
	if (bit > 0 && (cur >> bit - 1 & 1) == 0)
	{
		dfs(bit - 2, cur | (3 << bit - 1), next, res, pre);
	}
}

int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	
	int n, m, i, j, k;
	cin >> n >> m;
	
	ll ans = 0;
	dp[0][0] = 1;
	for (i = 1; i <= n; i++)
	{
		for (j = 0; j < 1 << m; j++)
		{
			dfs(m - 1, j, 0, dp[i], dp[i - 1][j]);
		}
	}
	
	cout << dp[n][0] << endl;
	
	
	return 0;
}