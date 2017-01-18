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

double cur[N][N][2][2];
double pre[N][N][2][2];
double dp[N][N];
double ans[N];
double c[N][N];
int a[N];
bool visit[N];

void solve()
{
	int n, k, i, j;
	cin >> n >> k;
	memset(ans, 0, sizeof(ans));
	memset(visit, 0, sizeof(visit));
	
	for (i = 1; i <= n; i++)
	{
		cin >> a[i];
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
	for (auto curSize : vec)
	{
		for (i = n; i >= 0; i--)
		{
			ans[i] = ans[i] * dp[curSize][0]; // dp[curSize][0] = 0
			for (j = 0; j < i; j++)
			{
				ans[i] += ans[j] * dp[curSize][i - j];
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
	
	// cur[usedBox][validKeyNum][curBox is used][firstBox is used]
	dp[1][1] = 1;
	cur[1][1][1][1] = 1;
	cur[0][0][0][0] = 1;
	for (i = 2; i <= 300; i++)
	{
		for (j = 0; j < i; j++)
		{
			for (k = 0; k <= j; k++)
			{
				for (p = 0; p < 2; p++)
				{
					for (q = 0; q < 2; q++)
					{
						pre[j][k][p][q] = cur[j][k][p][q];
						cur[j][k][p][q] = 0;
					}
				}
			}
		}
		
		for (j = 0; j < i; j++)
		{
			for (k = 0; k <= j; k++)
			{
				for (p = 0; p < 2; p++)
				{
					for (q = 0; q < 2; q++)
					{
						// whether using curBox
						for (r = 0; r < 2; r++)
						{
							add = !p && r;
							cur[j + r][k + add][r][q] += pre[j][k][p][q];
							
							if (p && q && r)
							{
								add = -1;
							}
							else if (!p && !q && r)
							{
								add = 1;
							}
							else
							{
								add = 0;
							}
							
							if (k + add >= i - j - r)
							{
								dp[i][j + r] += pre[j][k][p][q];
							}							
						}
					}
				}
			}
		}
	}
	
	
	int t; 
	cin >> t;
	while (t--)
	{
		solve();
	}
	
	
	return 0;
}