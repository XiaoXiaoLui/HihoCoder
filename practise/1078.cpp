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

const int N = 1 << 19;

int a[N];
bool lazy[N];
int tr[N];
int lazySet[N];

void down(int id, int left, int right)
{
	if (!lazy[id] || left == right)
	{
		return;
	}
	
	int mid = (right + left) / 2;
	lazy[2*id] = lazy[2*id + 1] = true;
	tr[2*id] = lazySet[id] * (mid - left + 1);
	tr[2*id + 1] = lazySet[id] * (right - mid);
	lazySet[2*id] = lazySet[2*id + 1] = lazySet[id];
	
	lazy[id] = false;
}

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
	tr[id] = tr[2*id] + tr[2*id + 1];
}

void update(int id, int left, int right, int start, int end, int value)
{
	down(id, left, right);
	if (left > end || right < start)
	{
		return;
	}
	
	if (left >= start && right <= end)
	{
		lazy[id] = true;
		tr[id] = (right - left + 1) * value;
		lazySet[id] = value;
		return;
	}
	
	int mid = (left + right) / 2;
	update(2*id, left, mid, start, end, value);
	update(2*id + 1, mid + 1, right, start, end, value);
	tr[id] = tr[2*id] + tr[2*id + 1];
}

int query(int id, int left, int right, int start, int end)
{
	down(id, left, right);
	if (left > end || right < start)
	{
		return 0;
	}
	
	if (left >= start && right <= end)
	{
		return tr[id];
	}
	int mid = (left + right) / 2;
	
	return query(2*id, left, mid, start, end) + query(2*id + 1, mid + 1, right, start, end);
}


int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int n, m, i, left, right, op, value;
	cin >> n;
	for (i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	build(1, 1, n);
	
	cin >> m;
	for (i = 1; i <= m; i++)
	{
		cin >> op;
		if (op == 0)
		{
			cin >> left >> right;
			int res = query(1, 1, n, left, right);
			cout << res << endl;
		}
		else
		{
			cin >> left >> right >> value;
			update(1, 1, n, left, right, value);
		}
	}
	
	return 0;
}