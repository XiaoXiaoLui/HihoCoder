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

const int N = 1e5 + 100;
const int INF = 1e9;

vector<pii> graph[N];
int d[N];

int main()
{
	//USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int n, m, i, j, u, v, w, startPos, endPos;
	scanf("%d%d%d%d", &n, &m, &startPos, &endPos);
	for (i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		graph[u].push_back({v, w});
		graph[v].push_back({u, w});
	}
	
	fill_n(d, N, INF);
	d[startPos] = 0;
	set<pii> S;
	S.insert({0, startPos});
	
	while (!S.empty())
	{
		u = S.begin()->second;
		S.erase(S.begin());
		if (u == endPos)
		{
			break;
		}
		
		for (auto e : graph[u])
		{
			v = e.first;
			w = e.second;
			
			if (d[u] + w < d[v])
			{
				auto iter = S.find({d[v], v});
				if (iter != S.end())
				{
					S.erase(iter);
				}
				
				d[v] = d[u] + w;
				S.insert({d[v], v});
			}
		}
	}
	
	printf("%d\n", d[endPos]);
	return 0;
}