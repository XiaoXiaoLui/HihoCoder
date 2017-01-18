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

const int N = 1e7 + 100;
char s[N];

void solve()
{
	int n, i, j, preNum, curNum, cnt;
	scanf("%d%s", &n, s);
	
	preNum = curNum = cnt = 0;
	
	bool ok = false;
	for (i = 0; i < n; i++)
	{
		for (j = i, curNum = 1; j < n && s[j + 1] == s[j]; j++, curNum++);
		
		if (i == 0 || s[i] != s[i - 1] + 1)
		{
			cnt = 1;
		}	
		else if (preNum <= curNum)
		{
			cnt++;
			if (cnt >= 3)
			{
				ok = true;
				break;
			}
			if (preNum != curNum)
			{
				cnt = 1;
			}
		}
		else
		{
			cnt = 2;
		}
		
		
		preNum = curNum;
		i = j;
	}
	
	if (ok)
	{
		printf("YES\n");
	}
	else
	{
		printf("NO\n");
	}
}


int main()
{
	USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	
	int t;
	scanf("%d", &t);
	while (t--)
	{
		solve();
	}
	return 0;
}