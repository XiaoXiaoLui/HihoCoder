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
	
	lazy[2*id] = lazy[2*id + 1] = true;
	tr[2*id] = tr[2*id + 1] = lazySet[id];
	lazySet[2*id] = lazySet[2*id + 1] = lazySet[id];
	
	lazy[id] = false;
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
		tr[id] = lazySet[id] = value;
		return;
	}
	
	int mid = (left + right) / 2;
	update(2*id, left, mid, start, end, value);
	update(2*id + 1, mid + 1, right, start, end, value);
	tr[id] = value;
}

void commit(int id, int left, int right)
{
	down(id, left, right);
	if (left == right)
	{
		a[left] = tr[id];
		return;
	}
	
	int mid = (left + right) / 2;
	commit(2*id, left, mid);
	commit(2*id + 1, mid + 1, right);
}

pii op[N];
bool counted[N];

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	
	int n, L, i, left, right;
	cin >> n >> L;
	set<int> S;
	map<int, int> hash;
	for (i = 1; i <= n; i++)
	{
		cin >> left >> right;
		S.insert(left);
		S.insert(right);
		op[i] = {left, right};
	}
	
	int num = 0;
	for (auto tmp : S)
	{
		hash[tmp] = ++num;
	}
	
	for (i = 1; i <= n; i++)
	{
		left = hash[op[i].first];
		right = hash[op[i].second];
		
		update(1, 1, num, left, right - 1, i);
	}
	commit(1, 1, num);
	
	int ans = 0;
	for (i = 1; i <= num; i++)
	{
		if (a[i] && !counted[a[i]])
		{
			ans++;
			counted[a[i]] = true;
		}
	}
	cout << ans << endl;
	
	return 0;
}