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

const int N = 250;

int parent[N];
string nameLst[N];
int deep[N];

int lca(int u, int v)
{
	while (u != v)
	{
		if (deep[u] >= deep[v])
		{
			u = parent[u];
		}
		else
		{
			v = parent[v];
		}
	}
	return u;
}

void dfsDeep(int u)
{
	if (u == 0 || deep[u])
	{
		return;
	}
	
	dfsDeep(parent[u]);
	deep[u] = deep[parent[u]] + 1;
}

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int n, m, i, u, v;
	string name1, name2;
	map<string, int> hash;
	cin >> n;
	
	int num = 0;
	nameLst[0] = "-1";
	for (i = 1; i <= n; i++)
	{
		cin >> name1 >> name2;
		if (hash.count(name1) == 0)
		{
			hash[name1] = ++num;
			nameLst[num] = name1;
		}
		if (hash.count(name2) == 0)
		{
			hash[name2] = ++num;
			nameLst[num] = name2;
		}
		
		u = hash[name1];
		v = hash[name2];
		parent[v] = u;
	}
	
	for (i = 1; i <= num; i++)
	{
		if (deep[i] == 0)
		{
			dfsDeep(i);
		}
	}
	
	cin >> m;
	for (i = 1; i <= m; i++)
	{
		cin >> name1 >> name2;
		if (name1 == name2)
		{
			cout << name1 << endl;
			continue;
		}
		u = hash[name1];
		v = hash[name2];
		
		int ret = lca(u, v);
		cout << nameLst[ret] << endl;
	}
	
	return 0;
}