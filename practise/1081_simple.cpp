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

const int N = 1005;
const int INF = 1e9 + 100;

vector<pii> graph[N];
int dist[N];
bool mark[N];

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int n, m, i, j, s, t, u, v, w;
	cin >> n >> m >> s >> t;
	for (i = 1; i <= m; i++)
	{
		cin >> u >> v >> w;
		graph[u].push_back({v, w});
		graph[v].push_back({u, w});
	}
	
	fill_n(dist, N, INF);
	dist[s] = 0;;
	for (i = 1; i <= n; i++)
	{
		u = 0;
		for (j = 1; j <= n; j++)
		{
			if (!mark[j] && dist[j] < dist[u])
			{
				u = j;
			}
		}
		
		// update dist
		for (auto e : graph[u])
		{
			v = e.first;
			w = e.second;
			dist[v] = min(dist[v], dist[u] + w);
		}
		
		mark[u] = true;
		
		if (u == t)
		{
			break;
		}
	}
	
	cout << dist[t] << endl;
	return 0;
}