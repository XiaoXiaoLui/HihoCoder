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
vector<int> path;
pii st[N][22];
int lg[N];
int pos[N];
int deep[N];
string nameLst[N];

void dfs(int u, int pre)
{
	deep[u] = deep[pre] + 1;
	path.push_back(u);
	for (auto v : graph[u])
	{
		if (v != pre)
		{
			dfs(v, u);
			path.push_back(u);
		}
	}
	pos[u] = path.size();
}

void buildRmq()
{
	int i, j, n;
	n = path.size();
	lg[1] = 0;
	for (i = 2; i < N; i++)
	{
		lg[i] = lg[i >> 1] + 1;
	}
	
	for (i = 1; i <= n; i++)
	{
		st[i][0] = {deep[path[i - 1]], path[i - 1]};
	}
	
	for (j = 1; j <= lg[n]; j++)
	{
		int len = 1 << j;
		for (i = 1; i + len - 1 <= n; i++)
		{
			st[i][j] = min(st[i][j - 1], st[i + len / 2][j - 1]);
		}
	}
}

pii rmq(int left, int right)
{
	int len = right - left + 1;
	int k = lg[len];
	
	return min(st[left][k], st[right - (1 << k) + 1][k]);
}

int lca(int u, int v)
{
	int left, right;
	left = pos[u];
	right = pos[v];
	if (left > right)
	{
		swap(left, right);
	}
	
	pii tmp = rmq(left, right);
	
	return tmp.second;
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
	buildRmq();
	
	cin >> m;
	for (i = 1; i <= m; i++)
	{
		cin >> name1 >> name2;
		u = dict[name1];
		v = dict[name2];
		
		int ret = lca(u, v);
		cout << nameLst[ret] << endl;
	}
	
	return 0;
}