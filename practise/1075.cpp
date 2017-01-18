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

const int N = 305;

double ans[N];
double c[N][N];
int a[N];
bool visit[N];

void solve()
{
	int n, k, i, j;
	scanf("%d%d", &n, &k);
	memset(ans, 0, sizeof(ans));
	memset(visit, 0, sizeof(visit));
	
	for (i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	
	vector<int> vec;
	for (i = 1; i <= n; i++)
	{
		if (!visit[i])
		{
			int cnt = 0;
			j = i;
			while (!visit[j])
			{
				cnt++;
				visit[j] = true;
				j = a[j];
			}
			vec.push_back(cnt);
		}
	}
	
	ans[0] = 1;
	int tot = 0;
	for (auto curSize : vec)
	{
		tot += curSize;
		for (i = tot; i >= 0; i--)
		{
			ans[i] = 0;
			for (j = 0; j < i; j++)
			{
				ans[i] += ans[j] * c[curSize][i - j];
			}
		}
	}
	
	printf("%.15lf\n", ans[k] / c[n][k]);
	
}

int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	
	// precal 
	int i, j, k, p, q, r, add;
	for (i = 0; i <= 300; i++)
	{
		c[i][0] = 1;
		for (j = 1; j <= i; j++)
		{
			c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
		}
	}
	
	int t; 
	scanf("%d", &t);
	while (t--)
	{
		solve();
	}
	
	
	return 0;
}