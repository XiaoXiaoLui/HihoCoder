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
bool bLazySet[N];
bool bLazyAdd[N];
int tr[N];
int setValue[N];
int addValue[N];

void down(int id, int left, int right)
{
	if (left == right)
	{
		return;
	}
	
	int mid = (right + left) / 2;
	int leftId = 2*id;
	int rightId = 2*id + 1;
	if (bLazySet[id])
	{
		bLazySet[leftId] = bLazySet[rightId] = true;
		setValue[leftId] = setValue[rightId] = setValue[id];
		
		tr[leftId] = setValue[id] * (mid - left + 1);
		tr[rightId] = setValue[id] * (right - mid);
		
		addValue[leftId] = addValue[rightId] = 0;
		bLazyAdd[leftId] = bLazyAdd[rightId] = false;
	}
	
	if (bLazyAdd[id])
	{
		bLazyAdd[leftId] = bLazyAdd[rightId] = true;
		tr[leftId] += addValue[id] * (mid - left + 1);
		tr[rightId] += addValue[id] * (right - mid);
		addValue[leftId] += addValue[id];
		addValue[rightId] += addValue[id];
		
	}
	
	bLazyAdd[id] = bLazySet[id] = false;
	addValue[id] = 0;
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

void updateAdd(int id, int left, int right, int start, int end, int value)
{
	down(id, left, right);
	if (left > end || right < start)
	{
		return;
	}
	
	if (left >= start && right <= end)
	{
		tr[id] += (right - left + 1) * value;
		bLazyAdd[id] = true;
		addValue[id] += value;
		return;
	}
	
	int mid = (left + right) / 2;
	updateAdd(2*id, left, mid, start, end, value);
	updateAdd(2*id + 1, mid + 1, right, start, end, value);
	tr[id] = tr[2*id] + tr[2*id + 1];
}

void updateSet(int id, int left, int right, int start, int end, int value)
{
	down(id, left, right);
	if (left > end || right < start)
	{
		return;
	}
	
	if (left >= start && right <= end)
	{
		bLazySet[id] = true;
		setValue[id] = value;
		tr[id] = (right - left + 1) * value;
		return;
	}
	
	int mid = (left + right) / 2;
	updateSet(2*id, left, mid, start, end, value);
	updateSet(2*id + 1, mid + 1, right, start, end, value);
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
	cin >> n >> m;
	n++;
	for (i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	build(1, 1, n);
	
	for (i = 1; i <= m; i++)
	{
		cin >> op >> left >> right >> value;
		left++;
		right++;
		if (op == 0)
		{
			updateAdd(1, 1, n, left, right, value);
		}
		else
		{
			updateSet(1, 1, n, left, right, value);
		}
		
		int res = tr[1];
		cout << res << endl;
	}
	
	return 0;
}