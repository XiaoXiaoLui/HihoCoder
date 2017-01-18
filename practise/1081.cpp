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
	set<pii> S;
	S.insert({dist[s], s});
	while (!S.empty())
	{
		u = S.begin()->second;
		S.erase(S.begin());
		if (u == t)
		{
			break;
		}
		
		// update dist
		for (auto e : graph[u])
		{
			v = e.first;
			w = e.second;
			
			if (dist[u] + w < dist[v])
			{
				auto iter = S.find({dist[v], v});
				if (iter != S.end())
				{
					S.erase(iter);
				}
				dist[v] = dist[u] + w;
				S.insert({dist[v], v});
			}
		}
	}
	
	cout << dist[t] << endl;
	return 0;
}