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

const int N = 1e5 + 100;
int dp[N];
int pre[N];
int w[600];
int v[600];

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	
	int n, m, i, j;
	cin >> n >> m;
	
	for (i = 1; i <= n; i++)
	{
		cin >> w[i] >> v[i];
	}
	
	for (i = 1; i <= n; i++)
	{
		memcpy(pre, dp, sizeof(dp));
		for (j = 0; j <= m; j++)
		{
			if (j >= w[i])
			{
				dp[j] = max(pre[j], dp[j - w[i]] + v[i]);
			}
			else
			{
				dp[j] = pre[j];
			}
		}
	}
	
	cout << dp[m] << endl;
	
	return 0;
}