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

const int N = 1 << 20;
const int INF = 1e9;

int a[N];
int tr[2*N];

void buildSegTree(int n)
{
	int i, j;
	fill_n(tr, 2*N, INF);
	for (i = 1; i <= n; i++)
	{
		tr[i - 1 + N] = a[i];
	}
	
	for (i = N - 1; i >= 1; i--)
	{
		tr[i] = min(tr[2*i], tr[2*i + 1]);
	}
}

int query(int left, int right)
{
	int l, r, res;
	res = INF;
	for (l = left - 1 + N, r = right + N; l < r; l >>= 1, r >>= 1)
	{
		if (l & 1)
		{
			res = min(res, tr[l++]);
		}
		if (r & 1)
		{
			res = min(res, tr[--r]);
		}
	}
	return res;
}

void update(int pos, int value)
{
	a[pos] = value;
	int id = (pos - 1 + N);
	tr[id] = value;
	
	for (id >>= 1; id >= 1; id >>= 1)
	{
		tr[id] = min(tr[2*id], tr[2*id + 1]);
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
	
	buildSegTree(n);
	
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
			update(left, right);
		}
	}
	
	
	return 0;
}