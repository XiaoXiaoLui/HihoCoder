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

const int N = 1e5 + 100;
int n, m;
int a[N];

bool ok(int t)
{
	int i, water, scoreHi, scoreHo;
	water = scoreHi = scoreHo = 0;
	for (i = 1; i <= n; i++)
	{
		water += t;
		if (water <= a[i])
		{
			scoreHi++;
			water = 0;
		}
		else
		{
			scoreHo++;
			water -= a[i];
		}
	}
	
	return scoreHo > scoreHi;
}

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int i;
	cin >> n >> m;
	for (i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	
	int left, right, mid;
	left = 0;
	right = m + 1;
	
	while (right - left > 1)
	{
		mid = (right + left) / 2;
		if (ok(mid))
		{
			right = mid;
		}
		else
		{
			left = mid;
		}
	}
	
	cout << right << endl;
	return 0;
}