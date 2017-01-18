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

const static int N = 105;
const static int INF = 1e9;
static vector<int> graph[N];
static int order[N];
static pii dp[N];
static int size[N];

bool dfs(int u, int pre)
{
	size[u] = order[u] ? 1 : 0;
	
	int minOrder, maxOrder;
	minOrder = INF;
	maxOrder = 0;
	
	for (auto v : graph[u])
	{
		if (v != pre)
		{
			int ret = dfs(v, u);
			if (!ret)
			{
				return false;
			}
			
			if (size[v])
			{
				size[u] += size[v];
				minOrder = min(minOrder, dp[v].first);
				maxOrder = max(maxOrder, dp[v].second);
			}
		}
	}
	
	if (order[u])
	{
		if (order[u] > minOrder)
		{
			return false;
		}
		minOrder = order[u];
		maxOrder = max(maxOrder, order[u]);
	}
	
	dp[u] = {minOrder, maxOrder};
	if (!size[u] || maxOrder - minOrder + 1 == size[u])
	{
		return true;
	}
	
	return false;
}

void solve()
{
	int n, m, i, u, v;
	// initialization
	for (i = 0; i < N; i++)
	{
		graph[i].clear();
		size[i] = 0;
		order[i] = 0;
	}
	
	cin >> n;
	for (i = 1; i < n; i++)
	{
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	cin >> m;
	for (i = 1; i <= m; i++)
	{
		cin >> u;
		order[u] = i;
	}
	
	int ret = dfs(1, 0);
	if (ret)
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}
}


int main()
{
	USE_IOSTREAM;
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