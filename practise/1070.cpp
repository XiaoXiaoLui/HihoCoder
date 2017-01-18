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

// Mo's algo

const int N = 1e4 + 50;
const int M = 110;
const int INF = 1e9;

int a[N];
int b[M];

void init(int n)
{
	int i;
	fill_n(b, M, INF);
	for (i = 1; i <= n; i++)
	{
		b[i / M] = min(b[i / M], a[i]);
	}
}

int query(int left, int right)
{
	int idStart, idEnd, id;
	idStart = left / M;
	idEnd = right / M;
	
	int res = INF;
	for (id = idStart + 1; id < idEnd; id++)
	{
		res  = min(res, b[id]);
	}
	
	for (int i = left; i < (idStart + 1) * M && i <= right; i++)
	{
		res = min(res, a[i]);
	}
	
	for (int i = max(idEnd * M, left); i <= right; i++)
	{
		res = min(res, a[i]);
	}
	
	return res;
}

void update(int pos, int value, int n)
{
	a[pos] = value;
	int id = pos / M;
	int start, end;
	start = max(id * M, 1);
	end = min(n + 1, (id + 1)*M);
	
	b[id] = INF;
	for (int i = start; i < end; i++)
	{
		b[id] = min(b[id], a[i]);
	}
}

int main()
{
	//USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	int n, m, i, j, left, right, op;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	
	init(n);
	
	cin >> m;
	for (i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &op, &left, &right);
		if (op == 0)
		{
			int ret = query(left, right);
			printf("%d\n", ret);
		}
		else
		{
			update(left, right, n);
		}
	}
	
	
	return 0;
}