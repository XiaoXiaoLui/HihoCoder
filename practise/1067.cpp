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

const int N = 2e5 + 100;
int dsu[N];
vector<int> graph[N];
vector<pii> query[N];
int visit[N];
int ans[N];
string nameLst[N];


void initDsu()
{
	for (int i = 1; i < N; i++)
	{
		dsu[i] = i;
	}
}

int find(int u)
{
	if (dsu[u] == u)
	{
		return u;
	}
	return dsu[u] = find(dsu[u]);
}

void dfs(int u, int pre)
{
	visit[u] = 1;
	int v, i;
	for (auto q : query[u])
	{
		v = q.first;
		i = q.second;
		if (visit[v] == 1)
		{
			ans[i] = v;
		}
		else if (visit[v] == 2)
		{
			ans[i] = find(v);
		}
	}
	
	for (auto v: graph[u])
	{
		if (v != pre)
		{
			dfs(v, u);
			dsu[v] = u;
		}
	}
	visit[u] = 2;
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
	
	cin >> m;
	for (i = 1; i <= m; i++)
	{
		cin >> name1 >> name2;
		u = dict[name1];
		v = dict[name2];
		if (u == v)
		{
			ans[i] = u;
		}
		
		query[u].push_back({v, i});
		query[v].push_back({u, i});
	}
	
	initDsu();
	dfs(1, 0);
	
	for (i = 1; i <= m; i++)
	{
		cout << nameLst[ans[i]] << endl;
	}
	
	return 0;
}