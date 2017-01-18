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

const ll MOD = 1e9 + 7;

int gcd(int a, int b)
{
	int c;
	while (b)
	{
		c = b;
		b = a % b;
		a = c;
	}
	return a;
}

// dp[sum][biggerThan][multiple of]
ll dp[105][105][55];

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	
	int n, m, j, k, i, first;
	cin >> n >> m;
	
	for (j = 0; j <= n; j++)
	{
		dp[0][j][1] = 1;
	}
	
	for (i = 1; i <= n; i++)
	{
		for (j = 0; j + 1 <= i; j++)
		{
			for (k = 1; k <= m; k++)
			{
				for (first = j + 1; first <= i; first++)
				{
					int nextMul = k / gcd(k, first);
					dp[i][j][k] = (dp[i][j][k] + dp[i - first][first][nextMul]) % MOD;
				}
			}
		}
	}
	
	cout << dp[n][0][m] << endl;
	return 0;
}