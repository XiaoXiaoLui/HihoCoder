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

const int N = 4e5 + 100;
vector<int> graph[N];
int st[N][22];
int lg[N];
int deep[N];
string nameLst[N];

void dfs(int u, int pre)
{
	deep[u] = deep[pre] + 1;
	st[u][0] = pre;
	for (auto v : graph[u])
	{
		if (v != pre)
		{
			dfs(v, u);
		}
	}
}

void buildSpareTable(int n)
{
	int i, j;
	lg[1] = 0;
	for (i = 2; i < N; i++)
	{
		lg[i] = lg[i >> 1] + 1;
	}
	
	for (j = 1; j <= lg[n]; j++)
	{
		for (i = 1; i <= n; i++)
		{
			int pre = st[i][j - 1];
			if (pre)
			{
				st[i][j] = st[pre][j - 1];
			}
			else
			{
				st[i][j] = 0;
			}
		}
	}
}

int lca(int u, int v, int n)
{
	if (deep[u] < deep[v])
	{
		swap(u, v);
	}
	
	int i;
	for (i = lg[n]; i >= 0; i--)
	{
		if (deep[st[u][i]] >= deep[v])
		{
			u = st[u][i];
		}
	}
	
	if (u == v)
	{
		return u;
	}
	
	// now u and v are in the same level
	for (i = lg[n]; i >= 0; i--)
	{
		if (st[u][i] != st[v][i])
		{
			u = st[u][i];
			v = st[v][i];
		}
	}
	
	return st[u][0];
}

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int n, m, i, u, v, num;
	string name1, name2;
	cin >> n;
	num = 0;
	map<string, int> dict;
	
	// first name is root
	while (n--)
	{
		cin >> name1 >> name2;
		if (dict.count(name1) == 0)
		{
			dict[name1] = ++num;
			nameLst[num] = name1;
		}
		if (dict.count(name2) == 0)
		{
			dict[name2] = ++num;
			nameLst[num] = name2;
		}
		
		u = dict[name2];
		v = dict[name1];
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	
	dfs(1, 0);
	buildSpareTable(num);
	
	cin >> m;
	for (i = 1; i <= m; i++)
	{
		cin >> name1 >> name2;
		u = dict[name1];
		v = dict[name2];
		
		int ret = lca(u, v, num);
		cout << nameLst[ret] << endl;
	}
	
	return 0;
}