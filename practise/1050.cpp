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

const int N = 1e5 + 100;

vector<int> graph[N];
int maxLen[N];
int maxDeep[N];

void dfs(int u, int pre)
{
	int mx1 = -1, mx2 = -1;
	for (auto v : graph[u])
	{
		if (v != pre)
		{
			dfs(v, u);
			if (maxDeep[v] > mx1)
			{
				mx2 = mx1;
				mx1 = maxDeep[v];
			}
			else if (maxDeep[v] > mx2)
			{
				mx2 = maxDeep[v];
			}
		}
	}
	
	maxLen[u] = mx1 + mx2 + 2;
	maxDeep[u] = mx1 + 1;
}

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	
	int n, i, u, v;
	cin >> n;
	for (i = 1; i < n; i++)
	{
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	dfs(1, 0);
	int ans = 0;
	for (i = 1; i <= n; i++)
	{
		ans = max(ans, maxLen[i]);
	}
	cout << ans << endl;
	return 0;
}