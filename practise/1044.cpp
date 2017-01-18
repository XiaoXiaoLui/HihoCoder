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

const int N = 1028;
const int INF = 1e9;
int dp[N][N];
int w[N];

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	//fill_n((int*)dp, N*N, -INF);
	
	int i, j, n, m, q, cnt;
	cin >> n >> m >> q;
	for (i = 1; i <= n; i++)
	{
		cin >> w[i];
	}
	
	int mask = (1 << m) - 1;
	for (i = 1; i <= n; i++)
	{
		for (j = 0; j < 1 << m; j++)
		{
			cnt = __builtin_popcount(j);
			if (cnt > q)
			{
				continue;
			}
			int preJ = j >> 1;
			int add = (j & 1) ? w[i] : 0;
			cnt -= j & 1;
			if (cnt == q)
			{
				dp[i][j] = dp[i - 1][preJ] + add;
			}
			else
			{
				dp[i][j] = max(dp[i - 1][preJ | 1 << m - 1], dp[i - 1][preJ]) + add;
			}
		}
	}
	
	int ans = 0;
	for (j = 0; j < 1 << m; j++)
	{
		cnt = __builtin_popcount(j);
		if (cnt > q)
		{
			continue;
		}
		ans = max(ans, dp[n][j]);
	}
	cout << ans << endl;
	
	return 0;
}