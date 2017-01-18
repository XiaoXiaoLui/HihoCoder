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


int dp[32][20005];
int a[32];
int b[32];

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	int n, i, j, k, m;
	cin >> n >> m;
	for (i = 1; i <= n; i++)
	{
		cin >> a[i] >> b[i];
	}
	
	int curW, sum;
	for (i = 1; i <= n; i++)
	{
		
		if (b[i] < 15)
		{
			for (j = 1; j <= m; j++)
			{
				dp[i][j] = dp[i - 1][j];
				if (j - b[i] >= 0)
				{
					dp[i][j] = max(dp[i][j], dp[i][j - b[i]] + a[i]);
				}
			}
		}
		else
		{
			for (j = 1; j <= m; j++)
			{
				dp[i][j] = dp[i - 1][j];
				int curW = b[i];
				int sum = curW;
				for (k = 1; j - sum >= 0; k++, curW = curW * 1.07 + 1e-9, sum += curW)
				{
					dp[i][j] = max(dp[i][j], dp[i - 1][j - sum] + k * a[i]);
				}
			}
		}
		/*
		for (j = 1; j <= m; j++)
		{
			dp[i][j] = dp[i - 1][j];
			curW = b[i];
			sum = curW;
			for (k = 1; j - sum >= 0; k++)
			{
				dp[i][j] = max(dp[i][j], dp[i - 1][j - sum] + k * a[i]);
				curW = curW * 1.07 + 1e-9;
				sum += curW;
			}
		}*/
	}
	
	cout << dp[n][m] << endl;
	
	return 0;
}