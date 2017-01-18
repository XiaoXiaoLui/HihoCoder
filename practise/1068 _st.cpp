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

const int N = 1e6 + 100;

int a[N];
int st[N][22];
int lg[N];

void buildSparseTable(int n)
{
	int i, j;
	lg[1] = 0;
	for (i = 2; i < N; i++)
	{
		lg[i] = lg[i >> 1] + 1;
	}
	
	for (i = 1; i <= n; i++)
	{
		st[i][0] = a[i];
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

int query(int left, int right)
{
	int len = right - left + 1;
	int k = lg[len];
	
	int res = min(st[left][k], st[right - (1 << k) + 1][k]);
	
	return res;
}

int main()
{
	//USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	int n, m, i, j, left, right;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	
	buildSparseTable(n);
	
	cin >> m;
	for (i = 1; i <= m; i++)
	{
		scanf("%d%d", &left, &right);
		int ret = query(left, right);
		printf("%d\n", ret);
	}
	
	
	return 0;
}