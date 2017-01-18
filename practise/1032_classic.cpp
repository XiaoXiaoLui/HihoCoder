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

const int N = 1e6 + 100;
char str[N];

int maxPalin(char *orgStr)
{
	static int dp[2*N];
	static char str[2*N];
	
	int i, j, len;
	for (i = 0; orgStr[i]; i++)
	{
		str[2*i] = orgStr[i];
		str[2*i + 1] = '\0';
	}
	len = 2*i - 1;
	
	int c, r, lc, lr;
	for (c = 0, lr = -1; c < len; c++)
	{
		r = c;
		if (lr > r)
		{
			r = min(lr, c + dp[2*lc - c]);
		}
		
		for (; r + 1 < len && 2*c - r - 1 >= 0 && str[r + 1] == str[2*c - r - 1]; r++);
		
		dp[c] = r - c;
		if (r > lr)
		{
			lr = r;
			lc = c;
		}
	}
	
	int ans = 0;
	for (i = 0; i < len; i++)
	{
		if (i & 1)
		{
			ans = max(ans, (dp[i] + 1) / 2 * 2);
		}
		else
		{
			ans = max(ans, dp[i] / 2 * 2 + 1);
		}
	}
	return ans;
	
}


int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int n;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", str);
		int ret = maxPalin(str);
		printf("%d\n", ret);
	}
	
	return 0;
}