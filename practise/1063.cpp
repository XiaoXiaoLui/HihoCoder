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
int rightDp[N][N];
int leftDp[N][N];
int nextVertex[N];
int preVertex[N];
int curDp[N];

vector<pii> graph[N];

void update(int &cur, int value)
{
	cur = min(cur, value);
}

void dfs(int u, int pre)
{
	int i, j, v, w, preV, nextV;
	
	for (auto e : graph[u])
	{
		v = e.first;
		w = e.second;
		if (v == pre)
		{
			continue;
		}
		dfs(v, u);
		preVertex[v] = preV;
		nextVertex[preV] = v;
		preV = v;
	}
	
	fill_n((int*)leftDp, N*N, INF);
	fill_n((int*)rightDp, N*N, INF);
	fill_n((int*)curDp, N, INF);
	fill_n(nextVertex, N, 0);
	fill_n(preVertex, N, 0);
	preV = nextV = v = 0;
	for (auto e : graph[u])
	{
		v = e.first;
		w = e.second;
		if (v == pre)
		{
			continue;
		}
		preVertex[v] = preV;
		nextVertex[preV] = v;
		preV = v;
	}
	
	// left to right dp
	rightDp[0][0] = 0;
	for (auto e : graph[u])
	{
		v = e.first;
		w = e.second;
		if (v == pre)
		{
			continue;
		}
		
		preV = preVertex[v];
		for (i = N - 1; i >= 0; i--)
		{
			// important!!!
			rightDp[v][i] = rightDp[preV][i];
			for (j = 0; j < i; j++)
			{
				update(rightDp[v][i], rightDp[preV][j] + g[v][i - j] + 2*w);
			}
		}
	}
	
	// right to left dp
	leftDp[0][0] = 0;
	for (auto iter = graph[u].rbegin(); iter != graph[u].rend(); iter++)
	{
		v = iter->first;
		w = iter->second;
		if (v == pre)
		{
			continue;
		}
		nextV = nextVertex[v];
		for (i = N - 1; i >= 0; i--)
		{
			// important!!!
			leftDp[v][i] = leftDp[nextV][i];
			for (j = 0; j < i; j++)
			{
				update(leftDp[v][i], leftDp[nextV][j] + g[v][i - j] + 2*w);
			}
		}
	}
	
	v = nextVertex[0];
	g[u][a[u]] = 0;
	for (i = N - 1; i >= 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			update(g[u][i], g[u][j] + leftDp[v][i - j]);
		}
	}
	
	f[u][a[u]] = 0;
	for (auto e : graph[u])
	{
		v = e.first;
		w = e.second;
		if (v == pre)
		{
			continue;
		}
		preV = preVertex[v];
		nextV = nextVertex[v];
		
		fill_n(curDp, N, INF);
		curDp[a[u]] = 0;
		
		// merge f[v]
		for (i = N - 1; i >= 0; i--)
		{
			for (j = 0; j < i; j++)
			{
				update(curDp[i], curDp[j] + f[v][i - j] + w);
			}
		}
		
		// merge rightDp[preV]
		for (i = N - 1; i >= 0; i--)
		{
			for (j = 0; j < i; j++)
			{
				update(curDp[i], curDp[j] + rightDp[preV][i - j]);
			}
		}
		
		// merge leftDp[nextV]
		for (i = N - 1; i >= 0; i--)
		{
			for (j = 0; j < i; j++)
			{
				update(curDp[i], curDp[j] + leftDp[nextV][i - j]);
			}
		}
		
		// update f[u]
		for (i = 0; i < N; i++)
		{
			update(f[u][i], curDp[i]);
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