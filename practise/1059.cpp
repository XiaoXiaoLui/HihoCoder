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

const int N = 2200;

int dp[N][N][2];
int f[N][N];

char s1[N];
char s2[N];

int main()
{
	//USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	//freopen("1.txt", "r", stdin);
	#endif
	
	scanf("%s%s", s1, s2);
	int n = strlen(s1);
	int m = strlen(s2);
	
	int i, j;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
		{
			if (s1[i - 1] == s2[j - 1])
			{
				f[i][j] = f[i - 1][j - 1] + 1;
			}
			int len = f[i][j];
			
			if (len >= 3)
			{
				dp[i][j][1] = dp[i - 3][j - 3][0] + 3;
				if (len > 3)
				{
					dp[i][j][1] = max(dp[i][j][1], dp[i - 1][j - 1][1] + 1);
				}
			}
			
			dp[i][j][0] = max(max(dp[i - 1][j][0], dp[i][j - 1][0]), dp[i][j][1]);
		}
	}
	
	printf("%d\n", dp[n][m][0]);
	
	return 0;
}