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

struct Edge
{
	int u;
	int v;
	int w;
	Edge(int uu, int vv, int ww)
	{
		u = uu;
		v = vv;
		w = ww;
	}
	
	bool operator < (const Edge &other) const
	{
		return w < other.w;
	}
	
	bool operator > (const Edge &other) const
	{
		return w > other.w;
	}
};


int parent[N];

void initDsu(int n)
{
	for (int i = 1; i <= n; i++)
	{
		parent[i] = i;
	}
}

int find(int u)
{
	if (parent[u] == u)
	{
		return u;
	}
	
	return parent[u] = find(parent[u]);
}

void merge(int u, int v)
{
	int pu = find(u);
	int pv = find(v);
	parent[pu] = pv;
}

int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int n, m, i, u, v, w;
	scanf("%d%d", &n, &m);
	
	priority_queue<Edge, vector<Edge>, greater<Edge> > Q;
	for (i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		//e[i] = {u, v, w};
		Q.push(Edge(u, v, w));
	}
	
	int ans = 0;
	int cnt = 0;
	initDsu(n);
	while (cnt < n - 1)
	{
		Edge e = Q.top();
		Q.pop();
		
		if (find(e.u) == find(e.v))
		{
			continue;
		}
		
		merge(e.u, e.v);
		ans += e.w;
		cnt++;
	}
	
	printf("%d\n", ans);
	return 0;
}