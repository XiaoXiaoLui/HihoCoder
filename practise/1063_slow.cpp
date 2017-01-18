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


const int N = 205;
const int INF =5e8;

int a[N];
int f[N][N];
int g[N][N];
int dp[N][N];

vector<pii> graph[N];

void dfs(int u, int pre)
{
	fill_n((int*)dp, N*N, INF);
	
	int i, j, v1, w1, v2, w2;
	g[u][a[u]] = 0;
	
	for (auto e1 : graph[u])
	{
		v1 = e1.first;
		w1 = e1.second;
		if (v1 == pre)
		{
			continue;
		}
		dfs(v1, u);
		for (i = N - 1; i >= 0; i--)
		{
			for (j = 0; j < i; j++)
			{
				g[u][i] = min(g[u][i], g[u][j] + g[v1][i - j] + 2*w1);
			}
		}
	}
	
	f[u][a[u]] = 0;
	for (auto e1 : graph[u])
	{
		v1 = e1.first;
		w1 = e1.second;
		if (v1 == pre)
		{
			continue;
		}
		
		dp[v1][a[u]] = 0;
		for (auto e2 : graph[u])
		{
			v2 = e2.first;
			w2 = e2.second;
			if (v2 == v1 || v2 == pre)
			{
				continue;
			}
			
			for (i = N - 1; i >= 0; i--)
			{
				for (j = 0; j < i; j++)
				{
					dp[v1][i] = min(dp[v1][i], dp[v1][j] + g[v2][i - j] + 2*w2);
				}
			}
		}
		
		for (i = N - 1; i >= 0; i--)
		{
			for (j = 0; j <= i; j++)
			{
				f[u][i] = min(f[u][i], dp[v1][j] + w1 + f[v1][i - j]);
			}
		}
	}
}

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int n, m, i,u, v, w;
	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	
	for (i = 1; i < n; i++)
	{
		cin >> u >> v >> w;
		graph[u].push_back({v, w});
		graph[v].push_back({u, w});
	}
	
	fill_n((int*)f, N*N, INF);
	fill_n((int*)g, N*N, INF);
	dfs(1, 0);
	int curMin = INF;
	for (i = N - 1; i >= 0; i--)
	{
		f[1][i] = min(f[1][i], curMin);
		curMin = min(curMin, f[1][i]);
	}
	
	cin >> m;
	for (i = 1; i <= m; i++)
	{
		cin >> w;
		int best = upper_bound((int*)f[1], (int*)f[1] + N, w) - (int*)f[1] - 1;
		cout << best << endl;
	}
	
	return 0;
}