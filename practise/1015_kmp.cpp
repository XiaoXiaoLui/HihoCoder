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
char pat[N];
char str[N];

int kmp(const char *str, const char *pat)
{
	static int next[N];
	int i, j, len;
	next[0] = -1;
	for (i = 1, j = -1; pat[i]; i++)
	{
		for (; j != -1 && pat[j + 1] != pat[i]; j = next[j]);
		
		if (pat[j + 1] == pat[i])
		{
			j++;
		}
		next[i] = j;
	}
	
	len = i;
	int res = 0;
	for (i = 0, j = -1; str[i]; i++)
	{
		for (; j != -1 && pat[j + 1] != str[i]; j = next[j]);
		
		if (pat[j + 1] == str[i])
		{
			j++;
		}
		
		if (j == len - 1)
		{
			res++;
			j = next[j];
		}
	}
	
	return res;
}


int main()
{
	// USE_IOSTREAM;
	#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	#endif
	int n, i;
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s%s", pat, str);
		int ret = kmp(str, pat);
		printf("%d\n", ret);
	}
	
	return 0;
}