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

const int N = 1e5 + 100;
const int INF = 2e9 + 2;
pii pos[N];
int a[N];
int b[N];

bool ok(int maxNum, int n, int R)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		a[i] = pos[i].second;
		b[i] = 0;
	}
	
	int tmp;
	for (i = 0, j = 0; i < n; i++)
	{
		while (j < i && a[i] > 0)
		{
			if (pos[j].first < pos[i].first - R || a[j] + b[j] == maxNum)
			{
				j++;
			}
			else
			{
				tmp = min(a[i], maxNum - a[j] - b[j]);
				a[i] -= tmp;
				b[j] += tmp;
			}
		}
		
		while (a[i] + b[i] > maxNum && pos[j].first <= pos[i].first + R)
		{
			if (j == i || b[j] == maxNum)
			{
				j++;
				continue;
			}
			
			tmp = min(a[i] + b[i] - maxNum, maxNum - b[j]);
			b[j] += tmp;
			a[i] -= tmp;
		}
		
		if (a[i] + b[i] > maxNum)
		{
			return false;
		}
	}
	
	return true;
}

void solve()
{
	int n, R, i, j;
	cin >> n >> R;
	
	bool noPeople = true;
	for (i = 0; i < n; i++)
	{
		cin >> pos[i].first >> pos[i].second;
		if (pos[i].second)
		{
			noPeople = false;
		}
	}
	
	if (noPeople)
	{
		cout << 0 << endl;
		return;
	}
	
	sort(pos, pos + n);
	
	/*
	// merge overlapped position
	for (i = 0, j = -1; i < n; i++)
	{
		if (j == -1 || pos[j].first != pos[i].first)
		{
			pos[++j] = pos[i];
		}
		else
		{
			pos[j].second += pos[i].second;
		}
	}
	
	n = j + 1;*/
	pos[n].first = INF;
	
	int left, right, mid;
	left = 0;
	right = INF;
	int ans = 0;
	while (right - left > 1)
	{
		mid = (right + left) / 2;
		if (ok(mid, n, R))
		{
			right = mid;
		}
		else
		{
			left = mid;
		}
	}
	
	cout << right << endl;
}

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
	
	return 0;
}