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
#include <queue>
#include <stack>
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

const int N = 13;

int g[N][N];
int dp[1 << 12][N];

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int n, m, i, j, k, u, v;
	cin >> n >> m;
	for (i = 1; i <= m; i++)
	{
		cin >> u >> v;
		u--;
		v--;
		g[u][v] = 1;
	}
	
	dp[1][0] = 1;
	for (i = 1; i < 1 << n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 1; k < n; k++)
			{
				if ((i >> k & 1) == 0 && g[j][k])
				{
					dp[i | 1 << k][k] += dp[i][j];
				}
			}
		}
	}
	
	int ans = 0;
	for (j = 1; j < n; j++)
	{
		if (g[j][0])
		{
			ans += dp[(1 << n) - 1][j];
		}
	}
	
	cout << ans  << endl;
	return 0;
}