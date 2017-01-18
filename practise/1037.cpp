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

const int N = 105;

int dp[N][N];
int a[N][N];

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	
	int n, i, j;
	cin >> n;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= i; j++)
		{
			cin >> a[i][j];
		}
	}
	
	fill_n((int*)dp, N*N, 0);
	for (i = n; i >= 1; i--)
	{
		for (j = 1; j <= i; j++)
		{
			dp[i][j] = a[i][j] + max(dp[i + 1][j], dp[i + 1][j + 1]);
		}
	}
	
	cout << dp[1][1] << endl;
	return 0;
}