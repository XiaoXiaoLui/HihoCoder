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

void build(int id, int left, int right)
{
	if (left == right)
	{
		tr[id] = a[left];
		return;
	}
	
	int mid = (left + right) / 2;
	build(2*id, left, mid);
	build(2*id + 1, mid + 1, right);
	tr[id] = min(tr[2*id], tr[2*id + 1]);
}

void update(int id, int left, int right, int pos, int value)
{
	if (pos < left || pos > right)
	{
		return;
	}
	
	if (left == right)
	{
		tr[id] = a[pos] = value;
		return;
	}
	
	int mid = (left + right) / 2;
	update(2*id, left, mid, pos, value);
	update(2*id + 1, mid + 1, right, pos, value);
	
	tr[id] = min(tr[2*id], tr[2*id + 1]);
}

// query [start, end]
int query(int id, int left, int right, int start, int end)
{
	if (right < start || left > end)
	{
		return INF;
	}
	
	if (left >= start && right <= end)
	{
		return tr[id];
	}
	
	int res, leftRes, rightRes, mid;
	mid = (left + right) / 2;
	leftRes = query(2*id, left, mid, start, end);
	rightRes = query(2*id + 1, mid + 1, right, start, end);
	
	res = min(leftRes, rightRes);
	return res;
}

int query(int left, int right, int n)
{
	return query(1, 1, n, left, right);
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
	
	build(1, 1, n);
	
	cin >> m;
	for (i = 1; i <= m; i++)
	{
		scanf("%d%d%d", &op, &left, &right);
		if (op == 0)
		{
			int ret = query(left, right, n);
			printf("%d\n", ret);
		}
		else
		{
			update(1, 1, n, left, right);
		}
	}
	
	
	return 0;
}