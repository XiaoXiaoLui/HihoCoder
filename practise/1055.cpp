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

vector<int> graph[N];
int a[N];
int dp[N][N];
int n, m;

void dfs(int u, int pre)
{
	int i, j;
	dp[u][1] = a[u];
	for (auto v : graph[u])
	{
		if (v == pre)
		{
			continue;
		}
		dfs(v, u);
		
		for (i = m; i > 0; i--)
		{
			for (j = 1; j < i; j++)
			{
				dp[u][i] = max(dp[u][i], dp[u][j] + dp[v][i - j]);
			}
		}
	}
}

int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	
	int i, u, v;
	cin >> n >> m;
	for (i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	
	for (i = 1; i < n; i++)
	{
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	dfs(1, 0);
	
	cout << dp[1][m] << endl;
	
	return 0;
}