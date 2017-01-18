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
const int INF = 1e9;

int g[N][N];
pii d[N];
int used[N];

int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int n, i, u, v;
	scanf("%d", &n);
	for (u = 1; u <= n; u++)
	{
		for (v = 1; v <= n; v++)
		{
			scanf("%d", &g[u][v]);
		}
	}
	
	fill_n((pii*)d, N, pii(INF, 0));
	int ans = 0;
	d[1] = {0, 0};
	for (i = 1; i <= n; i++)
	{
		u = 0;
		for (v = 1; v <= n; v++)
		{
			if (!used[v] && d[v] < d[u])
			{
				u = v;
			}
		}
		if (i != 1)
		{
			ans += d[u].first;
		}
		
		used[u] = true;
		// update
		for (v = 1; v <= n; v++)
		{
			if (!used[v])
			{
				d[v] = min(d[v], {g[u][v], u});
			}
		}
	}
	
	printf("%d\n", ans);
	return 0;
}