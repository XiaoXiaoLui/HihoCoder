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

const int N = 110;
const int INF = 1e9;
int g[N][N];

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	fill_n((int*)g, N*N, INF);
	
	int n, m, i, j, k, u, v, w;
	cin >> n >> m;
	for (i = 1; i <= m; i++)
	{
		cin >> u >> v >> w;
		g[u][v] = g[v][u] = min(g[u][v], w);
	}
	for (i = 1; i <= n; i++)
	{
		g[i][i] = 0;
	}
	
	for (k = 1; k <= n; k++)
	{
		for (j = 1; j <= n; j++)
		{
			for (i = 1; i <= n; i++)
			{
				g[i][j] = min(g[i][j], g[j][k] + g[k][i]);
			}
		}
	}
		
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			cout << g[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}