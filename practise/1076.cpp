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

const int N = 1e4 + 100;
const ll MOD = 1000000009;

ll dp[20][N];


void solve()
{
	int n, kNum, i, j, k;
	cin >> kNum >> n;
	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for (i = 1; n; i++)
	{
		int parity = n & 1;
		for (j = 0; j <= n && j <= kNum; j++)
		{
			int start = (parity ^ (j & 1));
			for (k = start; j + k <= n; k += 2)
			{
				dp[i][(j + k) / 2] = (dp[i][(j + k) / 2] + dp[i - 1][k]) % MOD;
			}
		}
		
		n >>= 1;
	}

	cout << dp[i - 1][0] << endl;
}

int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
	
	return 0;
}